..
  Copyright (c) 2004-present Fabien Potencier.
  Symfony™ is a trademark of Symfony SAS. All rights reserved.

  Documentation licensed under the Creative Commons Attribution-ShareAlike 3.0
  Unported License.
  The original work was translated from English into Brazilian Portuguese.
  https://github.com/symfony/symfony-docs/blob/-/LICENSE.md

  source_url: https://github.com/symfony/symfony-docs/blob/8.0/setup/_update_recipes.rst.inc
  revision: 11d87ad0540ac23e64a79d6769dae3d170a30bc7
  status: ready

3) Atualizando receitas
-----------------------

Com o tempo - e especialmente ao atualizar para uma nova versão de uma
biblioteca - uma versão atualizada da :ref:`receita <recipes-description>` pode
estar disponível.
Essas atualizações geralmente são pequenas - por exemplo, novos comentários em
um arquivo de configuração - mas é uma boa prática manter seus arquivos
sincronizados com as receitas.

O Symfony Flex oferece vários comandos para ajudar a atualizar suas receitas.
Certifique-se de fazer o commit de quaisquer alterações não relacionadas em que
você esteja trabalhando antes de começar:

.. versionadded:: 1.18

  O comando ``recipes:update`` foi introduzido no Symfony Flex 1.18.

.. code-block:: terminal

  # escolha uma receita desatualizada para atualizar
  $ composer recipes:update

  # atualize uma receita específica
  $ composer recipes:update symfony/framework-bundle

  # veja uma lista de todas as receitas instaladas e quais têm atualizações
  # disponíveis
  $ composer recipes

  # veja informações detalhadas sobre uma receita específica
  $ composer recipes symfony/framework-bundle

O comando ``recipes:update`` é inteligente: ele analisa a diferença entre a
receita quando você a instalou e a versão mais recente.
Em seguida, ele cria um patch e o aplica à sua aplicação.
Se houver algum conflito, você pode resolvê-lo como um conflito normal do
``git`` e fazer o commit normalmente.
