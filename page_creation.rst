..
  Copyright (c) 2004-present Fabien Potencier.
  Symfony™ is a trademark of Symfony SAS. All rights reserved.

  Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
  Unported License.
  The original work was translated from English into Brazilian Portuguese.
  https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

  source_url: https://github.com/symfony/symfony-docs/blob/8.0/page_creation.rst
  revision: 64c30da9266bf3aec686f4436a80827a3012d578
  status: ready

.. _creating-pages-in-symfony2:
.. _creating-pages-in-symfony:

Crie sua primeira página no Symfony
===================================

Criar uma nova página - seja ela uma página HTML ou um endpoint JSON - é um
processo de duas etapas:

#. **Crie um controlador**: um controlador é a função PHP que você escreve para
  construir a página.
  Você recebe as informações da requisição e as utiliza para criar um objeto
  ``Response`` do Symfony, que pode conter conteúdo HTML, uma string JSON ou até
  mesmo um arquivo binário como uma imagem ou PDF;

#. **Crie uma rota**: uma rota é a URL (por exemplo, ``/sobre``) da sua página e
  aponta para um controlador.

.. admonition:: Screencast
  :class: screencast

  Você prefere tutoriais em vídeo?
  Confira a série de screencasts `Cosmic Coding with Symfony`_

.. seealso::

  O Symfony *abraça* o ciclo de vida de requisição e resposta HTTP.
  Para saber mais, consulte :doc:`/introduction/http_fundamentals`.

Criando uma página: rota e controlador
--------------------------------------

.. tip::

  Antes de continuar, certifique-se de ter lido o artigo
  :doc:`Configuração </setup>` e de poder acessar sua nova aplicação Symfony no
  navegador.

Suponha que você queira criar uma página - ``/lucky/number`` - que gere um
número da sorte (bem, aleatório) e o imprima.
Para fazer isso, crie uma classe "Controller" e um método "number" dentro dela::

  <?php
  // src/Controller/LuckyController.php
  namespace App\Controller;

  use Symfony\Component\HttpFoundation\Response;

  class LuckyController
  {
      public function number(): Response
      {
          $number = random_int(0, 100);

          return new Response(
              '<html><body>Número da sorte: '.$number.'</body></html>'
          );
      }
  }

.. _annotation-routes:
.. _attribute-routes:

Agora você precisa associar essa função do controlador a uma URL pública (por
exemplo, ``/lucky/number``) para que o método ``number()`` seja chamado quando
uma pessoa usuária navegar até ela.
Essa associação é definida com o atributo ``#[Route]`` (em PHP, os `atributos`_
são usados para adicionar metadados ao código):

.. code-block:: diff

    // src/Controller/LuckyController.php

    // ...
  + use Symfony\Component\Routing\Attribute\Route;

    class LuckyController
    {
  +     #[Route('/lucky/number')]
        public function number(): Response
        {
            // Isso continua igual a antes.
        }
    }

É isso aí!
Se você estiver usando :ref:`o servidor web Symfony <symfony-cli-server>`, teste
isso acessando: http://localhost:8000/lucky/number

.. tip::

  O Symfony recomenda definir rotas como atributos para ter o código do
  controlador e sua configuração de rotas no mesmo local.
  No entanto, se preferir, você pode
  :doc:`definir rotas em arquivos separados </routing>` usando os formatos YAML
  ou PHP.

Se você vir um número da sorte sendo exibido, parabéns!
Mas antes de sair correndo para jogar na loteria, veja como isso funciona.
Lembra-se dos dois passos para criar uma página?

#. *Crie um controlador e um método*: esta é uma função onde *você* constrói a
  página e, por fim, retorna um objeto ``Response``.
  Você aprenderá mais sobre :doc:`controladores </controller>` em sua própria
  seção, incluindo como retornar respostas JSON;

#. *Crie uma rota*: em ``config/routes.yaml``, a rota define a URL da sua página
  (``path``) e qual ``controller`` chamar.
  Você aprenderá mais sobre :doc:`roteamento </routing>` em sua própria seção,
  incluindo como criar URLs *variáveis*.

O comando `bin/console`
-----------------------

Seu projeto já possui uma poderosa ferramenta de depuração: o comando
``bin/console``.
Tente executá-lo:

.. code-block:: terminal

  $ php bin/console

Você verá uma lista de comandos que podem fornecer informações de depuração,
ajudar a gerar código, gerar migrações de banco de dados e muito mais.
Conforme você instala mais pacotes, verá mais comandos.

Para obter uma lista de *todas* as rotas do seu sistema, use o comando
``debug:router``:

.. code-block:: terminal

  $ php bin/console debug:router

Você deverá ver sua rota ``app_lucky_number`` na lista:

.. code-block:: terminal

  ----------------  -------  --------------
  Name              Method   Path
  ----------------  -------  --------------
  app_lucky_number  ANY      /lucky/number
  ----------------  -------  --------------

Você também verá rotas de depuração além de ``app_lucky_number`` -- mais sobre
as rotas de depuração na próxima seção.

Você aprenderá sobre muitos outros comandos à medida que continuar!

.. tip::

  Se o seu shell for compatível, você também pode configurar o suporte para
  autocompletar comandos no console.
  Isso completa automaticamente comandos e outras entradas ao usar
  ``bin/console``.
  Consulte :ref:`o artigo do Console <console-completion-setup>` para obter mais
  informações sobre como configurar o autocompletar.

.. _web-debug-toolbar:

A Barra de Ferramentas de Depuração Web: um sonho de depuração
--------------------------------------------------------------

Um dos recursos *incríveis* do Symfony é a Barra de Ferramentas de Depuração
Web: uma barra que exibe uma *enorme* quantidade de informações de depuração na
parte inferior da sua página durante o desenvolvimento.
Tudo isso já vem incluído por padrão usando um
:ref:`pack do Symfony <symfony-packs>` chamado ``symfony/profiler-pack``.

Você verá uma barra escura na parte inferior da página.
Você aprenderá mais sobre todas as informações que ela contém ao longo do
caminho, mas sinta-se à vontade para experimentar: passe o mouse sobre os
diferentes ícones e clique neles para obter informações sobre roteamento,
desempenho, registro de logs e muito mais.

Renderizando um template
------------------------

Se você estiver retornando HTML do seu controlador, provavelmente desejará
renderizar um template.
Felizmente, o Symfony vem com o `Twig`_: uma linguagem de templates minimalista,
poderosa e bastante divertida.

Instale o pack twig com:

.. code-block:: terminal

  $ composer require twig

Certifique-se de que ``LuckyController`` estenda a classe base do Symfony
:class:`Symfony\\Bundle\\FrameworkBundle\\Controller\\AbstractController`:

.. code-block:: diff

    // src/Controller/LuckyController.php

    // ...
  + use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;

  - class LuckyController
  + class LuckyController extends AbstractController
    {
        // ...
    }

Agora, use o prático método ``render()`` para renderizar um template.
Passe para ele uma variável ``number`` para que você possa usá-la no Twig::

  // src/Controller/LuckyController.php
  namespace App\Controller;

  use Symfony\Component\HttpFoundation\Response;
  // ...

  class LuckyController extends AbstractController
  {
      #[Route('/lucky/number')]
      public function number(): Response
      {
          $number = random_int(0, 100);

          return $this->render('lucky/number.html.twig', [
              'number' => $number,
          ]);
      }
  }

Os arquivos de template ficam no diretório ``templates/``, que foi criado
automaticamente para você quando você instalou o Twig.
Crie um novo diretório ``templates/lucky`` com um novo arquivo
``number.html.twig`` dentro:

.. code-block:: html+twig

  {# templates/lucky/number.html.twig #}
  <h1>Seu número da sorte é {{ number }}</h1>

A sintaxe ``{{ number }}`` é usada para *imprimir* variáveis no Twig.
Atualize seu navegador para obter seu *novo* número da sorte!

  http://localhost:8000/lucky/number

Agora você pode estar se perguntando onde foi parar a Barra de Ferramentas de
Depuração Web: isso acontece porque não há uma tag ``</body>`` no template
atual.
Você pode adicionar o elemento body manualmente, ou estender ``base.html.twig``,
que contém todos os elementos HTML padrão.

No artigo :doc:`templates </templates>`, você aprenderá tudo sobre o Twig: como
fazer laços de repetição, renderizar outros templates e aproveitar seu poderoso
sistema de herança de layout.

Analisando a estrutura do projeto
---------------------------------

Ótima notícia!
Você já trabalhou nos diretórios mais importantes do seu projeto:

``config/``
  Contém... a configuração!
  Você configurará rotas, :doc:`serviços </service_container>` e pacotes.

``src/``
  Todo o seu código PHP está aqui.

``templates/``
  Todos os seus templates Twig estão aqui.

Na maioria das vezes, você trabalhará em ``src/``, ``templates/`` ou
``config/``.
Ao continuar lendo, você aprenderá o que pode ser feito em cada um deles.

E quanto aos outros diretórios do projeto?

``bin/``
  O famoso arquivo ``bin/console`` está aqui (e outros arquivos executáveis
  menos importantes).

``var/``
  É aqui que os arquivos criados automaticamente são armazenados, como arquivos
  de cache (``var/cache/``) e logs (``var/log/``).

``vendor/``
  Bibliotecas de terceiros (ou seja, "vendor") ficam aqui!
  Elas são baixadas pelo gerenciador de pacotes `Composer`_

``public/``
  Este é o diretório raiz do seu projeto: você coloca todos os arquivos
  publicamente acessíveis aqui.

E quando você instalar novos pacotes, novos diretórios serão criados
automaticamente quando necessário.

O que vem a seguir?
-------------------

Parabéns!
Você já está começando a aprender Symfony e a descobrir uma nova maneira de
construir aplicações bonitas, funcionais, rápidas e fáceis de manter.

OK, hora de terminar de aprender os fundamentos lendo estes artigos:

* :doc:`/routing`
* :doc:`/controller`
* :doc:`/templates`
* :doc:`/frontend`
* :doc:`/configuration`

Em seguida, aprenda sobre outros tópicos importantes como o
:doc:`container de serviços </service_container>`,
o :doc:`sistema de formulários </forms>`, o uso do :doc:`Doctrine </doctrine>`
(se precisar consultar um banco de dados) e muito mais!

Divirta-se!

Aprofunde-se nos fundamentos de HTTP e frameworks
-------------------------------------------------

.. toctree::
  :maxdepth: 1
  :glob:

  introduction/*

.. _`Twig`: https://twig.symfony.com
.. _`Composer`: https://getcomposer.org
.. _`Cosmic Coding with Symfony`: https://symfonycasts.com/screencast/symfony/setup
.. _`atributos`: https://www.php.net/manual/pt_BR/language.attributes.overview.php
