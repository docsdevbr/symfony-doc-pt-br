..
  Copyright (c) 2004-present Fabien Potencier.
  Symfony™ is a trademark of Symfony SAS. All rights reserved.

  Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
  Unported License.
  The original work was translated from English into Brazilian Portuguese.
  https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

  source_url: https://github.com/symfony/symfony-docs/blob/8.0/setup/_update_dep_errors.rst.inc
  revision: 7dfeaba1252a9b2d50280f667c87cad7a7e390dc
  status: ready

Erros de dependência
~~~~~~~~~~~~~~~~~~~~

Se você receber um erro de dependência, isso pode significar que você também
precisa atualizar outras bibliotecas que dependem das bibliotecas do Symfony.
Para permitir isso, passe a flag ``--with-all-dependencies``:

.. code-block:: terminal

  $ composer update "symfony/*" --with-all-dependencies

Isso atualiza ``symfony/*`` e *todos* os pacotes dos quais esses pacotes
dependem.
Ao usar restrições de versão rigorosas no ``composer.json``, você pode controlar
para quais versões cada biblioteca será atualizada.

Se isso ainda não funcionar, seu arquivo ``composer.json`` pode especificar uma
versão para uma biblioteca que não é compatível com a versão mais recente do
Symfony.
Nesse caso, a atualização dessa biblioteca para uma versão mais recente no
``composer.json`` pode resolver o problema.

Ou você pode ter problemas mais complexos, onde diferentes bibliotecas dependem
de versões conflitantes de outras bibliotecas.
Verifique a mensagem de erro para depurar.

Outro problema que pode ocorrer é que as dependências do projeto podem ser
instaladas no seu computador local, mas não no servidor remoto.
Isso geralmente acontece quando as versões do PHP são diferentes em cada
máquina.
A solução é adicionar a opção de configuração `platform`_ ao seu arquivo
``composer.json`` para definir a versão mais recente do PHP permitida para as
dependências (defina-a para a versão do PHP do servidor).

.. _`platform`: https://getcomposer.org/doc/06-config.md#platform
