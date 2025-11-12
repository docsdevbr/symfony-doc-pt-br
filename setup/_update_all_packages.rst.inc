..
  Copyright (c) 2004-present Fabien Potencier.
  Symfony™ is a trademark of Symfony SAS. All rights reserved.

  Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
  Unported License.
  The original work was translated from English into Brazilian Portuguese.
  https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

  source_url: https://github.com/symfony/symfony-docs/blob/8.0/setup/_update_all_packages.rst.inc
  revision: 3849004fcc56c63ced8441d0870e34137b5ab4b5
  status: ready

Atualizando outros pacotes
~~~~~~~~~~~~~~~~~~~~~~~~~~

Você também pode querer atualizar o restante das suas bibliotecas.
Se você fez um bom trabalho com suas `restrições de versão`_ no
``composer.json``, você pode fazer isso com segurança executando:

.. code-block:: terminal

  $ composer update

.. warning::

  Cuidado, se você tiver algumas `restrições de versão`_ não específicas no seu
  ``composer.json`` (por exemplo, ``dev-master``), isso pode atualizar algumas
  bibliotecas que não são do Symfony para novas versões que contêm alterações
  que quebram a compatibilidade com versões anteriores.

.. _`restrições de versão`: https://getcomposer.org/doc/articles/versions.md
