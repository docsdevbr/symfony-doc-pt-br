<!--
Copyright (c) 2004-present Fabien Potencier.
Symfony™ is a trademark of Symfony SAS. All rights reserved.

Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License.
The original work was translated from English into Brazilian Portuguese.
https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

source_url: https://github.com/symfony/symfony-docs/blob/8.0/quick_tour/the_big_picture.rst
revision: d637bfc33dab1a36645b990bb8b95f1ab67f2b2b
status: ready
-->

O panorama geral
================

Comece a usar o Symfony em 10 minutos!
Sério!
É tudo o que você precisa para entender os conceitos mais importantes e começar
a construir um projeto de verdade!

Se você já usou um framework web antes, deve se sentir em casa com o Symfony.
Se não, bem-vinda a uma maneira totalmente nova de desenvolver aplicações web.
O Symfony *abraça* as melhores práticas, mantém a compatibilidade com versões
anteriores (sim! Atualizar é sempre seguro e fácil!) e oferece suporte de longo
prazo.

.. _installing-symfony2:

Baixando o Symfony
------------------

Primeiro, certifique-se de ter instalado o `Composer`_ e ter o PHP 8.1 ou
superior.

Preparada? Em um terminal, execute:

.. code-block:: terminal

    $ composer create-project symfony/skeleton tour_rapido

Isso cria um novo diretório ``tour_rapido/`` com uma pequena, mas poderosa, nova
aplicação Symfony:

.. code-block:: text

    tour_rapido/
    ├─ .env
    ├─ bin/console
    ├─ composer.json
    ├─ composer.lock
    ├─ config/
    ├─ public/index.php
    ├─ src/
    ├─ symfony.lock
    ├─ var/
    └─ vendor/

Já podemos carregar o projeto em um navegador?
Sim!
Você pode configurar o
:doc:`Nginx ou o Apache </setup/web_server_configuration>` e configurar a raiz
do documento deles para o diretório ``public/``.
Mas, para desenvolvimento, é melhor instalar a ferramenta
:doc:`CLI Symfony </setup/symfony_cli>` e executar seu
:ref:`servidor web local <symfony-cli-server>` da seguinte forma:

.. code-block:: terminal

    $ symfony server:start

Experimente sua nova aplicação acessando ``http://localhost:8000`` em um
navegador!

.. image:: /_images/quick_tour/no_routes_page.png
    :alt: A página de boas-vindas padrão do Symfony.
    :class: with-browser

Fundamentos: rota, controlador, resposta
----------------------------------------

Nosso projeto tem apenas cerca de 15 arquivos, mas está pronto para se tornar
uma API elegante, uma aplicação web robusta ou um microsserviço.
O Symfony começa pequeno, mas cresce com você.

Mas antes de prosseguirmos, vamos nos aprofundar nos fundamentos construindo
nossa primeira página.

Em ``src/Controller``, crie uma nova classe ``DefaultController`` e um método
``index`` dentro::

    // src/Controller/DefaultController.php
    namespace App\Controller;

    use Symfony\Component\HttpFoundation\Response;
    use Symfony\Component\Routing\Attribute\Route;

    class DefaultController
    {
        #[Route('/', name: 'index')]
        public function index(): Response
        {
            return new Response('Olá!');
        }
    }

Pronto!
Tente acessar a página inicial: ``http://localhost:8000/``.
O Symfony vê que a URL corresponde à nossa rota e então executa o novo método
``index()``.

Um controlador é apenas uma função normal com *uma* regra: ele deve retornar um
objeto ``Response`` do Symfony.
Mas essa resposta pode conter qualquer coisa: texto simples, JSON ou uma página
HTML completa.

Mas o sistema de roteamento é *muito* mais poderoso.
Então, vamos tornar a rota mais interessante:

.. code-block:: diff

      // src/Controller/DefaultController.php
      namespace App\Controller;

      use Symfony\Component\HttpFoundation\Response;
      use Symfony\Component\Routing\Attribute\Route;

      class DefaultController
      {
    -     #[Route('/', name: 'index')]
    +     #[Route('/hello/{name}', name: 'index')]
          public function index(): Response
          {
              return new Response('Olá!');
          }
      }

A URL desta página mudou: *agora* é ``/hello/*``: o ``{name}`` funciona como um
curinga que corresponde a qualquer coisa.
E não é só isso!
Atualize o controlador também:

.. code-block:: diff

      <?php
      // src/Controller/DefaultController.php
      namespace App\Controller;

      use Symfony\Component\HttpFoundation\Response;
      use Symfony\Component\Routing\Attribute\Route;

      class DefaultController
      {
          #[Route('/hello/{name}', name: 'index')]
    -     public function index()
    +     public function index(string $name): Response
          {
    -         return new Response('Olá!');
    +         return new Response("Olá $name!");
          }
      }

Experimente a página acessando ``http://localhost:8000/hello/Symfony``.
Você deverá ver: Olá Symfony!
O valor de ``{name}`` na URL está disponível como um argumento ``$name`` no seu
controlador.

Mas, ao usar atributos, a rota e o controlador ficam bem próximos um do outro.
Precisa de outra página?
Adicione outra rota e método em ``DefaultController``::

    // src/Controller/DefaultController.php
    namespace App\Controller;

    use Symfony\Component\HttpFoundation\Response;
    use Symfony\Component\Routing\Attribute\Route;

    class DefaultController
    {
        // ...

        #[Route('/simplicity', methods: ['GET'])]
        public function simple(): Response
        {
            return new Response('Simples! Fácil! Ótimo!');
        }
    }

O roteamento pode fazer *ainda* mais, mas deixaremos isso para outra ocasião!
No momento, nossa aplicação precisa de mais recursos!
Como um motor de template, logging, ferramentas de depuração e muito mais.

Continue lendo em :doc:`/quick_tour/flex_recipes`.

.. _`Composer`: https://getcomposer.org/
