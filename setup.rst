<!--
Copyright (c) 2004-present Fabien Potencier.
Symfony™ is a trademark of Symfony SAS. All rights reserved.

Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License.
The original work was translated from English into Brazilian Portuguese.
https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

source_url: https://github.com/symfony/symfony-docs/blob/8.0/setup.rst
revision: be230a850ad40aa5e14f28b2be85b3ab33bbe93c
status: ready
-->

Instalando e configurando o Framework Symfony
=============================================

.. admonition:: Screencast
  :class: screencast

  Você prefere tutoriais em vídeo?
  Confira a série de screencasts `Cosmic Coding with Symfony`_

.. _symfony-tech-requirements:

Requisitos técnicos
-------------------

Antes de criar sua primeira aplicação Symfony, você deve:

* Instalar o PHP 8.4 ou superior e estas extensões PHP (que são instaladas e
  habilitadas por padrão na maioria das instalações do PHP 8): `Ctype`_,
  `iconv`_, `PCRE`_, `Session`_, `SimpleXML`_ e `Tokenizer`_;
* `Instalar o Composer`_, que é usado para instalar pacotes PHP.

.. _setup-symfony-cli:

Além disso, `instale a CLI do Symfony`_.
Isso é opcional, mas te dá um binário útil chamado ``symfony`` que fornece todas
as ferramentas necessárias para desenvolver e executar sua aplicação Symfony
localmente.

O binário ``symfony`` também fornece uma ferramenta para verificar se o seu
computador atende a todos os requisitos.
Abra o terminal do console e execute este comando:

.. code-block:: terminal

  $ symfony check:requirements

.. note::

  A CLI do Symfony é de código aberto e você pode contribuir com ela no
  `repositório GitHub symfony-cli/symfony-cli`_.

.. _creating-symfony-applications:

Criando aplicações Symfony
--------------------------

Abra seu terminal de console e execute qualquer um destes comandos para criar
uma nova aplicação Symfony:

.. code-block:: terminal

  # execute isto se você estiver construindo uma aplicação web tradicional
  $ symfony new minha-aplicacao --version="8.0.x-dev" --webapp

  # execute isto se você estiver construindo um microsserviço, aplicação de
  # console ou API
  $ symfony new minha-aplicacao --version="8.0.x-dev"

A única diferença entre esses dois comandos é o número de pacotes instalados por
padrão.
A opção ``--webapp`` instala pacotes extras para fornecer tudo o que você
precisa para construir uma aplicação web.

Se você não estiver usando o binário do Symfony, execute estes comandos para
criar a nova aplicação Symfony usando o Composer:

.. code-block:: terminal

  # execute isto se você estiver construindo uma aplicação web tradicional
  $ composer create-project symfony/skeleton:"8.0.x-dev" minha-aplicacao
  $ cd minha-aplicacao
  $ composer require webapp

  # execute isto se você estiver construindo um microsserviço, aplicação de
  # console ou API
  $ composer create-project symfony/skeleton:"8.0.x-dev" minha-aplicacao

Não importa qual comando você execute para criar a aplicação Symfony.
Todos eles criarão um novo diretório ``minha-aplicacao/``, baixarão algumas
dependências para ele e até gerarão os diretórios e arquivos básicos necessários
para começar.
Em outras palavras, sua nova aplicação está pronta!

.. note::

  Os diretórios de cache e logs do projeto (por padrão, ``<projeto>/var/cache/``
  e ``<projeto>/var/log/``) devem ser graváveis pelo servidor web.
  Se você tiver algum problema, leia como
  :doc:`configurar permissões para aplicações Symfony </setup/file_permissions>`.

.. _install-existing-app:

Configurando um projeto Symfony existente
-----------------------------------------

Além de criar novos projetos Symfony, você também trabalhará em projetos já
criados por outras pessoas desenvolvedoras.
Nesse caso, você só precisa obter o código do projeto e instalar as dependências
com o Composer.
Supondo que seu time use Git, configure seu projeto com os seguintes comandos:

.. code-block:: terminal

  # Clone o projeto para baixar seu conteúdo
  $ cd projects/
  $ git clone ...

  # Faça com que o Composer instale as dependências do projeto em vendor/
  $ cd meu-projeto/
  $ composer install

Você provavelmente também precisará personalizar seu arquivo
:ref:`.env <config-dot-env>` e realizar algumas outras tarefas específicas do
projeto (por exemplo, criar um banco de dados).
Ao trabalhar em uma aplicação Symfony existente pela primeira vez, pode ser útil
executar este comando, que exibe informações sobre o projeto:

.. code-block:: terminal

  $ php bin/console about

Executando aplicações Symfony
-----------------------------

Em produção, você deve instalar um servidor web como Nginx ou Apache e
:doc:`configurá-lo para executar o Symfony </setup/web_server_configuration>`.
Este método também pode ser usado se você não estiver usando o servidor web
local do Symfony para desenvolvimento.

.. _symfony-binary-web-server:

No entanto, para desenvolvimento local, a maneira mais conveniente de executar o
Symfony é usando o :ref:`servidor web local <symfony-cli-server>` fornecido pela
ferramenta CLI do Symfony.
Este servidor local oferece, entre outras coisas, suporte para HTTP/2,
requisições simultâneas, TLS/SSL e geração automática de certificados de
segurança.

Abra o terminal do console, acesse o novo diretório do projeto e inicie o
servidor web local da seguinte forma:

.. code-block:: terminal

  $ cd meu-projeto/
  $ symfony server:start

Abra seu navegador e navegue até ``http://localhost:8000/``.
Se tudo estiver funcionando, você verá uma página de boas-vindas.
Mais tarde, quando terminar de trabalhar, pare o servidor pressionando
``Ctrl+C`` no seu terminal.

.. tip::

  O servidor web funciona com qualquer aplicação PHP, não apenas com projetos
  Symfony, portanto, é uma ferramenta de desenvolvimento genérica muito útil.

Integração do Docker com o Symfony
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Se você quiser usar o Docker com o Symfony, consulte :doc:`/setup/docker`.

.. _symfony-flex:
.. _flex-quick-intro:

Instalando pacotes
------------------

Uma prática comum no desenvolvimento de aplicações Symfony é instalar pacotes
(o Symfony os chama de :doc:`bundles </bundles>`) que fornecem funcionalidades
prontas para uso.
Os pacotes geralmente exigem alguma configuração antes de serem usados (editar
algum arquivo para habilitar o pacote, criar algum arquivo para adicionar alguma
configuração inicial, etc.).

Na maioria das vezes, essa configuração pode ser automatizada e é por isso que o
Symfony inclui o `Symfony Flex`_, uma ferramenta para simplificar a
instalação/remoção de pacotes em aplicações Symfony.
Tecnicamente falando, o Symfony Flex é um plugin do Composer instalado por
padrão ao criar uma nova aplicação Symfony e que **automatiza as tarefas mais
comuns das aplicações Symfony**.

.. tip::

  Você também pode adicionar o Symfony Flex a um projeto existente usando o
  comando `setup/flex`.

O Symfony Flex modifica o comportamento dos comandos ``require``, ``update`` e
``remove`` do Composer para fornecer recursos avançados.
Considere o seguinte exemplo:

.. code-block:: terminal

  $ cd meu-projeto/
  $ composer require logger

Se você executar esse comando em uma aplicação Symfony que não usa Flex, verá um
erro do Composer explicando que ``logger`` não é um nome de pacote válido.
No entanto, se a aplicação tiver o Symfony Flex instalado, esse comando instala
e habilita todos os pacotes necessários para usar o logger oficial do Symfony.

.. _recipes-description:

Isso é possível porque muitos pacotes/bundles do Symfony definem **"receitas"**,
que são um conjunto de instruções automatizadas para instalar e habilitar
pacotes em aplicações Symfony.
O Flex registra as receitas instaladas em um arquivo ``symfony.lock``, que deve
ser enviado para o seu repositório de código.

As receitas do Symfony Flex são fornecidas pela comunidade e armazenadas em dois
repositórios públicos:

* `Repositório principal de receitas`_, é uma lista selecionada de receitas para
  pacotes mantidos de alta qualidade.
  O Symfony Flex procura apenas neste repositório por padrão.

* `Repositório de receitas contribuídas`_, contém todas as receitas criadas pela
  comunidade.
  Todas elas têm garantia de funcionamento, mas seus pacotes associados podem
  não ser mantidos.
  O Symfony Flex solicitará sua permissão antes de instalar qualquer uma dessas
  receitas.

Leia a `Documentação de receitas do Symfony`_ para saber tudo sobre como criar
receitas para seus próprios pacotes.

.. _symfony-packs:

Packs do Symfony
~~~~~~~~~~~~~~~~

Às vezes, um único recurso requer a instalação de vários pacotes e bundles.
Em vez de instalá-los individualmente, o Symfony fornece **packs**, que são
metapacotes do Composer que incluem diversas dependências.

Por exemplo, para adicionar recursos de depuração à sua aplicação, você pode
executar o comando ``composer require --dev debug``.
Isso instala o ``symfony/debug-pack``, que por sua vez instala vários pacotes,
como ``symfony/debug-bundle``, ``symfony/monolog-bundle``,
``symfony/var-dumper``, etc.

Você não verá a dependência ``symfony/debug-pack`` no seu ``composer.json``,
pois o Flex descompacta o pack automaticamente.
Isso significa que ele adiciona apenas os pacotes reais como dependências (por
exemplo, você verá um novo ``symfony/var-dumper`` em ``require-dev``).

.. _security-checker:

Verificando vulnerabilidades de segurança
-----------------------------------------

O binário ``symfony`` criado quando você instalou o
:ref:`CLI do Symfony <setup-symfony-cli>` fornece um comando para verificar se
as dependências do seu projeto contêm alguma vulnerabilidade de segurança conhecida:

.. code-block:: terminal

  $ symfony check:security

Uma boa prática de segurança é executar este comando regularmente para poder
atualizar ou substituir dependências comprometidas o mais rápido possível.
A verificação de segurança é feita localmente, buscando o
``banco de dados de avisos de segurança do PHP`_ público, para que seu arquivo
``composer.lock`` não seja enviado pela rede.

O comando ``check:security`` termina com um código de saída diferente de zero se
alguma de suas dependências for afetada por uma vulnerabilidade de segurança
conhecida.
Dessa forma, você pode adicioná-lo ao processo de construção do seu projeto e
aos seus fluxos de trabalho de integração contínua para fazê-los falhar quando
houver vulnerabilidades.

.. tip::

  Em serviços de integração contínua, você pode verificar vulnerabilidades de
  segurança executando o comando ``composer audit``.
  Isso usa os mesmos dados internamente que ``check:security``, mas não requer a
  instalação de toda a CLI do Symfony durante a integração contínua ou em
  workers de integração contínua.

Versões LTS do Symfony
----------------------

De acordo com o
:doc:`Processo de lançamento do Symfony</contributing/community/releases>`,
as versões de "suporte de longo prazo" (ou LTS, para abreviar) são publicadas a
cada dois anos.
Confira os `Lançamentos do Symfony`_ para saber qual é a versão LTS mais
recente.

Por padrão, o comando que cria novas aplicações Symfony usa a versão estável
mais recente.
Se você quiser usar uma versão LTS, adicione a opção ``--version``:

.. code-block:: terminal

  # usa a versão LTS mais recente
  $ symfony new minha-aplicacao --version=lts

  # usa a próxima versão do Symfony a ser lançada (ainda em desenvolvimento)
  $ symfony new minha-aplicacao --version=next

  # você também pode selecionar uma versão específica do Symfony
  $ symfony new minha-aplicacao --version="6.4.*"

Os atalhos ``lts`` e ``next`` estão disponíveis apenas ao usar o Symfony para
criar novos projetos.
Se você usa o Composer, precisa informar a versão exata:

.. code-block:: terminal

  $ composer create-project symfony/skeleton:"6.4.*" minha-aplicacao

A aplicação de demonstração do Symfony
--------------------------------------

`A aplicação de demonstração do Symfony`_ é uma aplicação totalmente funcional
que mostra a maneira recomendada de desenvolver aplicações Symfony.
É uma ótima ferramenta de aprendizado para iniciantes no Symfony e seu código
contém muitos comentários e notas úteis.

Execute este comando para criar um novo projeto baseado na aplicação de
demonstração do Symfony:

.. code-block:: terminal

  $ symfony new minha-aplicacao --demo

Comece a programar!
-------------------

Com a configuração concluída, é hora de
:doc:`Criar sua primeira página no Symfony </page_creation>`.

Saiba mais
----------

.. toctree::
  :maxdepth: 1
  :glob:

  setup/docker
  setup/homestead
  setup/web_server_configuration
  setup/*

.. _`Cosmic Coding with Symfony`: https://symfonycasts.com/screencast/symfony
.. _`Instalar o Composer`: https://getcomposer.org/download/
.. _`instale a CLI do Symfony`: https://symfony.com/download
.. _`repositório GitHub symfony-cli/symfony-cli`: https://github.com/symfony-cli/symfony-cli
.. _`A aplicação de demonstração do Symfony`: https://github.com/symfony/demo
.. _`Symfony Flex`: https://github.com/symfony/flex
.. _`banco de dados de avisos de segurança do PHP`: https://github.com/FriendsOfPHP/security-advisories
.. _`Lançamentos do Symfony`: https://symfony.com/releases
.. _`Repositório principal de receitas`: https://github.com/symfony/recipes
.. _`Repositório de receitas contribuídas`: https://github.com/symfony/recipes-contrib
.. _`Documentação de receitas do Symfony`: https://github.com/symfony/recipes/blob/master/README.rst
.. _`iconv`: https://www.php.net/book.iconv
.. _`Session`: https://www.php.net/book.session
.. _`Ctype`: https://www.php.net/book.ctype
.. _`Tokenizer`: https://www.php.net/book.tokenizer
.. _`SimpleXML`: https://www.php.net/book.simplexml
.. _`PCRE`: https://www.php.net/book.pcre
