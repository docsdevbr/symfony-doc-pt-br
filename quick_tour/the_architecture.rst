<!--
Copyright (c) 2004-present Fabien Potencier.
Symfony™ is a trademark of Symfony SAS. All rights reserved.

Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License.
The original work was translated from English into Brazilian Portuguese.
https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

source_url: https://github.com/symfony/symfony-docs/blob/8.0/quick_tour/the_architecture.rst
revision: fffb06d80528cca1bba16bed8e6a8f08eca09d05
status: ready
-->

A arquitetura
=============

Você é uma pessoa fantástica!
Quem imaginaria que você ainda estaria aqui depois das primeiras duas partes?
Seus esforços serão recompensados em breve.
As duas primeiras partes não analisaram muito profundamente a arquitetura do
framework.
Como isso diferencia o Symfony dos demais frameworks, vamos nos aprofundar na
arquitetura agora.

Adicionando logs
----------------

Uma nova aplicação Symfony é micro: é basicamente um sistema de roteamento e
controlador.
Mas graças ao Flex, instalar mais recursos é simples.

Quer um sistema de logs?
Sem problemas:

.. code-block:: terminal

  $ composer require logger

Isso instala e configura (por meio de uma receita) a poderosa biblioteca
`Monolog`_.
Para usar o logger em um controlador, adicione um novo argumento com o tipo
``LoggerInterface``::

  // src/Controller/DefaultController.php
  namespace App\Controller;

  use Psr\Log\LoggerInterface;
  use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
  use Symfony\Component\HttpFoundation\Response;
  use Symfony\Component\Routing\Attribute\Route;

  class DefaultController extends AbstractController
  {
      #[Route('/hello/{name}', methods: ['GET'])]
      public function index(string $name, LoggerInterface $logger): Response
      {
          $logger->info("Dizendo olá para $name!");

          // ...
      }
  }

Pronto!
A nova mensagem de log será gravada em ``var/log/dev.log``.
O caminho do arquivo de log ou até mesmo um método diferente de log pode ser
configurado atualizando um dos arquivos de configuração adicionados pela
receita.

Serviços e autowiring
---------------------

Mas espere!
Algo *muito* legal aconteceu.
O Symfony leu o tipo ``LoggerInterface`` e automaticamente descobriu que deveria
nos passar o objeto Logger!
Isso se chama *autowiring*.

Todo trabalho feito em uma aplicação Symfony é feito por um *objeto*: o objeto
Logger cria logs de coisas e o objeto Twig renderiza templates.
Esses objetos são chamados de *serviços* e são *ferramentas* que ajudam você a
construir recursos avançados.

Para tornar a vida mais incrível, você pode pedir ao Symfony para lhe passar um
serviço usando um tipo.
Quais outras classes ou interfaces possíveis você poderia usar?
Descubra executando:

.. code-block:: terminal

  $ php bin/console debug:autowiring

    # esta é apenas uma *pequena* amostra da saída...

    Describes a logger instance.
    Psr\Log\LoggerInterface - alias:monolog.logger

    Request stack that controls the lifecycle of requests.
    Symfony\Component\HttpFoundation\RequestStack - alias:request_stack

    RouterInterface is the interface that all Router classes must implement.
    Symfony\Component\Routing\RouterInterface - alias:router.default

    [...]

Este é apenas um breve resumo da lista completa!
E à medida que você adicionar mais pacotes, esta lista de ferramentas aumentará!

Criando serviços
----------------

Para manter seu código organizado, você pode até criar seus próprios serviços!
Suponha que você queira gerar uma saudação aleatória (por exemplo, "Olá",
"E aí", etc.).
Em vez de colocar este código diretamente no seu controlador, crie uma nova
classe::

  // src/GreetingGenerator.php
  namespace App;

  class GreetingGenerator
  {
      public function getRandomGreeting(): string
      {
          $greetings = ['Olá', 'E aí', 'Aloha'];
          $greeting = $greetings[array_rand($greetings)];

          return $greeting;
      }
  }

Ótimo!
Você pode usá-la imediatamente no seu controlador::

  // src/Controller/DefaultController.php
  namespace App\Controller;

  use App\GreetingGenerator;
  use Psr\Log\LoggerInterface;
  use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
  use Symfony\Component\HttpFoundation\Response;
  use Symfony\Component\Routing\Attribute\Route;

  class DefaultController extends AbstractController
  {
      #[Route('/hello/{name}', methods: ['GET'])]
      public function index(string $name, LoggerInterface $logger, GreetingGenerator $generator): Response
      {
          $greeting = $generator->getRandomGreeting();

          $logger->info("Dizendo $greeting para $name!");

          // ...
      }
  }

Pronto!
O Symfony instanciará o ``GreetingGenerator`` automaticamente e o passará como
argumento.
Mas, poderíamos *também* mover a lógica do logger para ``GreetingGenerator``?
Sim!
Você pode usar autowiring dentro de um serviço para acessar *outros* serviços.
A única diferença é que isso é feito no construtor:

.. code-block:: diff

    <?php
    // src/GreetingGenerator.php
  + use Psr\Log\LoggerInterface;

    class GreetingGenerator
    {
  +     public function __construct(
  +         private LoggerInterface $logger,
  +     ) {
  +     }

        public function getRandomGreeting(): string
        {
            // ...

  +        $this->logger->info('Usando a saudação: '.$greeting);

             return $greeting;
        }
    }

Sim!
Isso também funciona: sem configuração, sem perda de tempo.
Continue codificando!

A extensão Twig e a autoconfiguração
------------------------------------

Graças ao gerenciamento de serviços do Symfony, você pode *estender* o Symfony
de várias maneiras, como criando um assinante de eventos ou um eleitor de
segurança para regras de autorização complexas.
Vamos adicionar um novo filtro ao Twig chamado ``greet``.
Como?
Crie uma classe com sua lógica::

  // src/Twig/GreetExtension.php
  namespace App\Twig;

  use App\GreetingGenerator;
  use Twig\Attribute\AsTwigFilter;

  class GreetExtension
  {
      public function __construct(
          private GreetingGenerator $greetingGenerator,
      ) {
      }

      #[AsTwigFilter('greet')]
      public function greetUser(string $name): string
      {
          $greeting =  $this->greetingGenerator->getRandomGreeting();

          return "$greeting $name!";
      }
  }

Depois de criar apenas *um* arquivo, você pode usar isto imediatamente:

.. code-block:: html+twig

  {# templates/default/index.html.twig #}
  {# Imprimirá algo como "Ei Symfony!" #}
  <h1>{{ name|greet }}</h1>

Como isso funciona?
O Symfony percebe que sua classe usa o atributo ``#[AsTwigFilter]`` e, portanto,
*automaticamente* a registra como uma extensão do Twig.
Isso se chama autoconfiguração e funciona para *muitas* coisas.
Crie uma classe e, em seguida, estenda uma classe base (ou implemente uma
interface).
O Symfony cuida do resto.

Incrivelmente rápido: o contêiner em cache
------------------------------------------

Depois de ver o quanto o Symfony lida automaticamente, você pode estar se
perguntando: "Isso não prejudica o desempenho?"
Na verdade, não!
O Symfony é incrivelmente rápido.

Como isso é possível?
O sistema de serviços é gerenciado por um objeto muito importante chamado
"contêiner".
A maioria dos frameworks possui um contêiner, mas o do Symfony é único porque
ele é *armazenado em cache*.
Quando você carregou sua primeira página, todas as informações do serviço foram
compiladas e salvas.
Isso significa que os recursos de autowiring e autoconfiguração não adicionam
*nenhuma* sobrecarga!
Isso também significa que você recebe *ótimos* erros: o Symfony inspeciona e
valida *tudo* quando o contêiner é construído.

Agora você deve estar se perguntando o que acontece quando você atualiza um
arquivo e o cache precisa ser reconstruído?
Gostei da sua ideia!
Ele é inteligente o suficiente para reconstruir no próximo carregamento de
página.
Mas esse é realmente o tópico da próxima seção.

Desenvolvimento versus produção: ambientes
------------------------------------------

Uma das principais funções de um framework é facilitar a depuração!
E nossa aplicação está *repleta* de ótimas ferramentas para isso: a barra de
ferramentas de depuração web é exibida na parte inferior da página, os erros são
grandes, bonitos e explícitos, e qualquer cache de configuração é reconstruído
automaticamente sempre que necessário.

Mas e quando você implanta em produção?
Precisaremos ocultar essas ferramentas e otimizar para velocidade!

Isso é resolvido pelo sistema de *ambientes* do Symfony.
As aplicações Symfony começam com três ambientes: ``dev``, ``prod`` e ``test``.
Você pode definir opções para ambientes específicos nos arquivos de configuração
do diretório ``config/`` usando a palavra-chave especial ``when@``:

.. configuration-block::

  .. code-block:: yaml

    # config/packages/routing.yaml
    framework:
        router:
            utf8: true

    when@prod:
        framework:
            router:
                strict_requirements: null

  .. code-block:: xml

    <!-- config/packages/framework.xml -->
    <?xml version="1.0" encoding="UTF-8" ?>
    <container xmlns="http://symfony.com/schema/dic/services"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:framework="http://symfony.com/schema/dic/symfony"
        xsi:schemaLocation="http://symfony.com/schema/dic/services
            https://symfony.com/schema/dic/services/services-1.0.xsd
            http://symfony.com/schema/dic/symfony
            https://symfony.com/schema/dic/symfony/symfony-1.0.xsd">

        <framework:config>
            <framework:router utf8="true"/>
        </framework:config>

        <when env="prod">
            <framework:config>
                <framework:router strict-requirements="null"/>
            </framework:config>
        </when>
    </container>

  .. code-block:: php

    // config/packages/framework.php
    namespace Symfony\Component\DependencyInjection\Loader\Configurator;

    use Symfony\Config\FrameworkConfig;

    return static function (FrameworkConfig $framework, ContainerConfigurator $container): void {
        $framework->router()
            ->utf8(true)
        ;

        if ('prod' === $container->env()) {
            $framework->router()
                ->strictRequirements(null)
            ;
        }
    };

Esta é uma ideia *poderosa*: ao alterar uma parte da configuração (o ambiente),
sua aplicação deixa de ser uma experiência amigável à depuração e se torna
otimizada para velocidade.

Ah, como você altera o ambiente?
Altere a variável de ambiente ``APP_ENV`` de ``dev`` para ``prod``:

.. code-block:: diff

    # .env
  - APP_ENV=dev
  + APP_ENV=prod

Mas quero falar mais sobre variáveis de ambiente a seguir.
Altere o valor de volta para ``dev``: ferramentas de depuração são ótimas quando
você está trabalhando localmente.

Variáveis de ambiente
---------------------

Cada aplicação contém configurações diferentes em cada servidor - como
informações de conexão de banco de dados ou senhas.
Como elas devem ser armazenadas?
Em arquivos?
Ou de outra forma?

O Symfony segue as melhores práticas da indústria, armazenando configurações
baseadas em servidor como variáveis de *ambiente*.
Isso significa que o Symfony funciona *perfeitamente* com sistemas de
implantação de Plataforma como Serviço (PaaS), bem como com o Docker.

Mas definir variáveis de ambiente durante o desenvolvimento pode ser um
problema.
É por isso que sua aplicação carrega automaticamente um arquivo ``.env``.
As chaves neste arquivo se tornam variáveis de ambiente e são lidas pela sua
aplicação:

.. code-block:: bash

  # .env
  ###> symfony/framework-bundle ###
  APP_ENV=dev
  APP_SECRET=cc86c7ca937636d5ddf1b754beb22a10
  ###< symfony/framework-bundle ###

A princípio, o arquivo não contém muita coisa.
Mas, à medida que sua aplicação cresce, você adicionará mais configurações
conforme necessário.
Mas, na verdade, fica muito mais interessante!
Suponha que sua aplicação precise de um ORM de banco de dados.
Vamos instalar o ORM Doctrine:

.. code-block:: terminal

  $ composer require doctrine

Graças a uma nova receita instalada pelo Flex, olhe novamente para o arquivo
``.env``:

.. code-block:: diff

    ###> symfony/framework-bundle ###
    APP_ENV=dev
    APP_SECRET=cc86c7ca937636d5ddf1b754beb22a10
    ###< symfony/framework-bundle ###

  + ###> doctrine/doctrine-bundle ###
  + # ...
  + DATABASE_URL=mysql://db_user:db_password@127.0.0.1:3306/db_name
  + ###< doctrine/doctrine-bundle ###

A nova variável de ambiente ``DATABASE_URL`` foi adicionada *automaticamente* e
já é referenciada pelo novo arquivo de configuração ``doctrine.yaml``.
Ao combinar variáveis de ambiente e Flex, você está usando as melhores práticas
da indústria sem nenhum esforço extra.

Continue!
---------

Pode parecer loucura, mas depois de ler esta parte, você deve estar confortável
com as partes *importantes* do Symfony.
Tudo no Symfony foi projetado para não atrapalhar você, para que você possa
continuar codificando e adicionando recursos, tudo com a velocidade e a
qualidade que você exige.

Isso é tudo para o tour rápido.
Da autenticação a formulários e cache, há muito mais para descobrir.
Pronta para se aprofundar nesses tópicos agora?
Não procure mais - acesse o :doc:`/index` oficial e escolha o guia que desejar.

.. _`Monolog`: https://github.com/Seldaek/monolog
