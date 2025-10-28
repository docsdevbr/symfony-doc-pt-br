<!--
Copyright (c) 2004-present Fabien Potencier.
Symfony™ is a trademark of Symfony SAS. All rights reserved.

Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License.
The original work was translated from English into Brazilian Portuguese.
https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

source_url: https://github.com/symfony/symfony-docs/blob/8.0/quick_tour/flex_recipes.rst
revision: 826615a830fee0c70c9d1d240ba7a9ef21070008
status: ready
-->

Flex: componha sua aplicação
============================

Após ler a primeira parte deste tutorial, você decidiu que vale a pena gastar
mais 10 minutos com o Symfony.
Ótima escolha!
Nesta segunda parte, você aprenderá sobre o Symfony Flex: a ferramenta incrível
que torna a adição de novos recursos tão simples quanto executar um comando.
É também a razão pela qual o Symfony é ideal para um pequeno microsserviço ou
uma aplicação enorme.
Curioso?
Perfeito!

Symfony: comece micro!
----------------------

A menos que você esteja construindo uma API pura (mais sobre isso em breve!),
você provavelmente vai querer renderizar HTML.
Para isso, você usará o `Twig`_.
O Twig é um motor de templates flexível, rápido e seguro para PHP.
Ele torna seus templates mais legíveis e concisos; também os torna mais
amigáveis para web designers.

O Twig já está instalado em nossa aplicação?
Na verdade, ainda não!
E isso é ótimo!
Quando você inicia um novo projeto Symfony, ele é *pequeno*: apenas as
dependências mais críticas são incluídas no seu arquivo ``composer.json``:

.. code-block:: text

  "require": {
      "...",
      "symfony/console": "^6.1",
      "symfony/flex": "^2.0",
      "symfony/framework-bundle": "^6.1",
      "symfony/yaml": "^6.1"
  }

Isso torna o Symfony diferente de qualquer outro framework PHP!
Em vez de começar com uma aplicação *volumosa* com *todos* os recursos possíveis
que você possa precisar, uma aplicação Symfony é pequena, simples e *rápida*.
E você tem controle total sobre o que adicionar.

Receitas e apelidos do Flex
---------------------------

Então, como podemos instalar e configurar o Twig?
Executando um único comando:

.. code-block:: terminal

  $ composer require twig

Duas coisas *muito* interessantes acontecem nos bastidores graças ao Symfony
Flex: um plugin do Composer que já está instalado em nosso projeto.

Primeiro, ``twig`` não é o nome de um pacote do Composer: é um *apelido* do Flex
que aponta para ``symfony/twig-bundle``.
O Flex resolve esse apelido para o Composer.

E segundo, o Flex instala uma *receita* para o pacote ``symfony/twig-bundle``.
O que é uma receita?
É uma maneira de uma biblioteca se configurar automaticamente adicionando e
modificando arquivos.
Graças às receitas, adicionar recursos é simples e automatizado: instale um
pacote e pronto!

Você pode encontrar uma lista completa de receitas e apelidos em
`RECIPES.md no repositório de receitas`_.

O que esta receita fez?
Além de habilitar automaticamente o recurso em ``config/bundles.php``, ela
adicionou 3 coisas:

``config/packages/twig.yaml``
  Um arquivo de configuração que configura o Twig com padrões sensatos.

``config/packages/test/twig.yaml``
  Um arquivo de configuração que altera algumas opções do Twig ao executar
  testes.

``templates/``
  Este é o diretório onde os arquivos de template ficarão.
  A receita também adicionou um arquivo de layout ``base.html.twig``.

Twig: renderizando um template
------------------------------

Graças ao Flex, após um comando, você pode começar a usar o Twig imediatamente:

.. code-block:: diff

    <?php
    // src/Controller/DefaultController.php
    namespace App\Controller;

    use Symfony\Component\Routing\Attribute\Route;
    use Symfony\Component\HttpFoundation\Response;
  + use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;

  - class DefaultController
  + class DefaultController extends AbstractController
    {
         #[Route('/hello/{name}', methods: ['GET'])]
         public function index(string $name): Response
         {
  -        return new Response("Olá $name!");
  +        return $this->render('default/index.html.twig', [
  +            'name' => $name,
  +        ]);
         }
    }

Ao estender ``AbstractController``, você agora tem acesso a uma série de métodos
e ferramentas de atalho, como ``render()``.
Crie o novo template:

.. code-block:: html+twig

  {# templates/default/index.html.twig #}
  <h1>Olá {{ name }}</h1>

Pronto!
A sintaxe ``{{ name }}`` imprimirá a variável ``name`` passada pelo controlador.
Se você é uma pessoa nova no Twig, seja bem-vinda!
Você aprenderá mais sobre sua sintaxe e poder mais tarde.

Mas, por enquanto, a página contém *apenas* a tag ``h1``.
Para dar a ela um layout HTML, estenda ``base.html.twig``:

.. code-block:: html+twig

  {# templates/default/index.html.twig #}
  {% extends 'base.html.twig' %}

  {% block body %}
      <h1>Olá {{ name }}</h1>
  {% endblock %}

Isso se chama herança de template: nossa página agora herda a estrutura HTML de
``base.html.twig``.

Profiler: paraíso da depuração
------------------------------

Um dos recursos *mais legais* do Symfony ainda nem está instalado!
Vamos consertar isso:

.. code-block:: terminal

  $ composer require profiler

Sim!
Este é outro apelido!
E o Flex *também* instala outra receita, que automatiza a configuração do
Profiler do Symfony.
Qual é o resultado?
Atualize a página!

Está vendo aquela barra preta na parte inferior?
Essa é a barra de ferramentas de depuração web e ela é sua nova melhor amiga.
Ao passar o mouse sobre cada ícone, você pode obter informações sobre qual
controlador foi executado, informações de desempenho, acertos e erros de cache e
muito mais.
Clique em qualquer ícone para acessar o *profiler*, onde você tem dados ainda
*mais* detalhados de depuração e desempenho!

Ah, e à medida que você instala mais bibliotecas, você obtém mais ferramentas
(como um ícone da barra de ferramentas de depuração web que mostra consultas ao
banco de dados).

Agora você pode usar o profiler diretamente porque ele se configurou *sozinho*
graças à receita.
O que mais podemos instalar?

Rico suporte à API
------------------

Você está construindo uma API?
Você já pode retornar JSON de qualquer controlador::

  // src/Controller/DefaultController.php
  namespace App\Controller;

  use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
  use Symfony\Component\HttpFoundation\JsonResponse;
  use Symfony\Component\Routing\Attribute\Route;

  class DefaultController extends AbstractController
  {
      // ...

      #[Route('/api/hello/{name}', methods: ['GET'])]
      public function apiHello(string $name): JsonResponse
      {
          return $this->json([
              'name' => $name,
              'symfony' => 'rocks',
          ]);
      }
  }

Mas para uma API *verdadeiramente* rica, tente instalar a `API Platform`_:

.. code-block:: terminal

  $ composer require api

Este é um apelido para ``api-platform/api-pack``
:ref:`Symfony pack <symfony-packs>`, que possui dependências de vários outros
pacotes, como os componentes Validator e Security do Symfony, além do ORM
Doctrine.
De fato, o Flex instalou *5* receitas!

Mas, como de costume, podemos começar a usar a nova biblioteca imediatamente.
Quer criar uma API avançada para uma tabela ``product``?
Crie uma entidade ``Product`` e atribua a ela o atributo ``#[ApiResource]``::

  // src/Entity/Product.php
  namespace App\Entity;

  use ApiPlatform\Core\Annotation\ApiResource;
  use Doctrine\ORM\Mapping as ORM;

  #[ORM\Entity]
  #[ApiResource]
  class Product
  {
      #[ORM\Id]
      #[ORM\GeneratedValue(strategy: 'AUTO')]
      #[ORM\Column(type: 'integer')]
      private int $id;

      #[ORM\Column(type: 'string')]
      private string $name;

      #[ORM\Column(type: 'integer')]
      private int $price;

      // ...
  }

Pronto!
Agora você tem endpoints para listar, adicionar, atualizar e excluir produtos!
Não acredita em mim?
Liste suas rotas executando:

.. code-block:: terminal

  $ php bin/console debug:router

  ------------------------------ -------- -------------------------------------
   Name                           Method   Path
  ------------------------------ -------- -------------------------------------
   api_products_get_collection    GET      /api/products.{_format}
   api_products_post_collection   POST     /api/products.{_format}
   api_products_get_item          GET      /api/products/{id}.{_format}
   api_products_put_item          PUT      /api/products/{id}.{_format}
   api_products_delete_item       DELETE   /api/products/{id}.{_format}
   ...
  ------------------------------ -------- -------------------------------------

.. _ easily-remove-recipes:

Removendo receitas
------------------

Ainda não se convenceu?
Sem problemas: remova a biblioteca:

.. code-block:: terminal

  $ composer remove api

O Flex *desinstalará* as receitas: removendo arquivos e desfazendo alterações
para colocar sua aplicação de volta ao estado original.
Experimente sem preocupações.

Mais recursos, arquitetura e velocidade
---------------------------------------

Espero que você esteja tão animada com o Flex quanto eu!
Mas ainda temos *mais um* capítulo e é o mais importante até agora.
Quero mostrar como o Symfony permite que você crie recursos rapidamente *sem*
sacrificar a qualidade ou o desempenho do código.
É tudo sobre o contêiner de serviços e este é o superpoder do Symfony.
Continue lendo: sobre :doc:`/quick_tour/the_architecture`.

.. _`RECIPES.md no repositório de receitas`: https://github.com/symfony/recipes/blob/flex/main/RECIPES.md
.. _`API Platform`: https://api-platform.com/
.. _`Twig`: https://twig.symfony.com/
