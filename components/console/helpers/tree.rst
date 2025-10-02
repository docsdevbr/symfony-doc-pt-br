Tree Helper
===========

The Tree Helper allows you to build and display tree structures in the console.
It's commonly used to render directory hierarchies, but you can also use it to render
any tree-like content, such us organizational charts, product category trees, taxonomies, etc.

Rendering a Tree
----------------

The :method:`Symfony\\Component\\Console\\Helper\\TreeHelper::createTree` method
creates a tree structure from an array and returns a :class:`Symfony\\Component\\Console\\Helper\\Tree`
object that can be rendered in the console.

Rendering a Tree from an Array
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can build a tree from an array by passing the array to the
:method:`Symfony\\Component\\Console\\Helper\\TreeHelper::createTree` method
inside your console command::

    namespace App\Command;

    use Symfony\Component\Console\Attribute\AsCommand;
    use Symfony\Component\Console\Helper\TreeHelper;
    use Symfony\Component\Console\Helper\TreeNode;
    use Symfony\Component\Console\Style\SymfonyStyle;

    #[AsCommand(name: 'app:my-command', description: '...')]
    class MyCommand
    {
        // ...

        public function __invoke(SymfonyStyle $io): int
        {
            $node = TreeNode::fromValues([
                'config/',
                'public/',
                'src/',
                'templates/',
                'tests/',
            ]);

            $tree = TreeHelper::createTree($io, $node);
            $tree->render();

            // ...
        }
    }

This exampe would output the following:

.. code-block:: terminal

    ├── config/
    ├── public/
    ├── src/
    ├── templates/
    └── tests/

The given contents can be defined in a multi-dimensional array::

    $tree = TreeHelper::createTree($io, null, [
        'src' =>  [
            'Command',
            'Controller' => [
                'DefaultController.php',
            ],
            'Kernel.php',
        ],
        'templates' => [
            'base.html.twig',
        ],
    ]);

    $tree->render();

The above code will output the following tree:

.. code-block:: terminal

    ├── src
    │   ├── Command
    │   ├── Controller
    │   │   └── DefaultController.php
    │   └── Kernel.php
    └── templates
        └── base.html.twig

Building a Tree Programmatically
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you don't know the tree elements beforehand, you can build the tree programmatically
by creating a new instance of the :class:`Symfony\\Component\\Console\\Helper\\Tree`
class and adding nodes to it::

    use Symfony\Component\Console\Helper\TreeHelper;
    use Symfony\Component\Console\Helper\TreeNode;

    $root = new TreeNode('my-project/');
    // you can pass a string directly or create a TreeNode object
    $root->addChild('src/');
    $root->addChild(new TreeNode('templates/'));

    // create nested structures by adding child nodes to other nodes
    $testsNode = new TreeNode('tests/');
    $functionalTestsNode = new TreeNode('Functional/');
    $testsNode->addChild($functionalTestsNode);
    $root->addChild($testsNode);

    $tree = TreeHelper::createTree($io, $root);
    $tree->render();

This example outputs:

.. code-block:: terminal

    my-project/
    ├── src/
    ├── templates/
    └── tests/
        └── Functional/

If you prefer, you can build the array of elements programmatically and then
create and render the tree like this::

    $tree = TreeHelper::createTree($io, null, $array);
    $tree->render();

You can also build part of the tree from an array and then add other nodes::

    $node = TreeNode::fromValues($array);
    $node->addChild('templates');
    // ...
    $tree = TreeHelper::createTree($io, $node);
    $tree->render();

Customizing the Tree Style
--------------------------

Built-in Tree Styles
~~~~~~~~~~~~~~~~~~~~

The tree helper provides a few built-in styles that you can use to customize the
output of the tree.

**Default**::

    TreeHelper::createTree($io, $node, [], TreeStyle::default());

This outputs:

.. code-block:: terminal

    ├── config
    │   ├── packages
    │   └── routes
    │      ├── framework.yaml
    │      └── web_profiler.yaml
    ├── src
    │   ├── Command
    │   ├── Controller
    │   │   └── DefaultController.php
    │   └── Kernel.php
    └── templates
       └── base.html.twig

**Box**::

    TreeHelper::createTree($io, $node, [], TreeStyle::box());

This outputs:

.. code-block:: terminal

    ┃╸ config
    ┃  ┃╸ packages
    ┃  ┗╸ routes
    ┃     ┃╸ framework.yaml
    ┃     ┗╸ web_profiler.yaml
    ┃╸ src
    ┃  ┃╸ Command
    ┃  ┃╸ Controller
    ┃  ┃  ┗╸ DefaultController.php
    ┃  ┗╸ Kernel.php
    ┗╸ templates
       ┗╸ base.html.twig

**Double box**::

    TreeHelper::createTree($io, $node, [], TreeStyle::doubleBox());

This outputs:

.. code-block:: terminal

    ╠═ config
    ║  ╠═ packages
    ║  ╚═ routes
    ║    ╠═ framework.yaml
    ║    ╚═ web_profiler.yaml
    ╠═ src
    ║  ╠═ Command
    ║  ╠═ Controller
    ║  ║  ╚═ DefaultController.php
    ║  ╚═ Kernel.php
    ╚═ templates
      ╚═ base.html.twig

**Compact**::

    TreeHelper::createTree($io, $node, [], TreeStyle::compact());

This outputs:

.. code-block:: terminal

    ├ config
    │ ├ packages
    │ └ routes
    │   ├ framework.yaml
    │   └ web_profiler.yaml
    ├ src
    │ ├ Command
    │ ├ Controller
    │ │ └ DefaultController.php
    │ └ Kernel.php
    └ templates
      └ base.html.twig

**Light**::

    TreeHelper::createTree($io, $node, [], TreeStyle::light());

This outputs:

.. code-block:: terminal

    |-- config
    |   |-- packages
    |   `-- routes
    |       |-- framework.yaml
    |       `-- web_profiler.yaml
    |-- src
    |   |-- Command
    |   |-- Controller
    |   |   `-- DefaultController.php
    |   `-- Kernel.php
    `-- templates
        `-- base.html.twig

**Minimal**::

    TreeHelper::createTree($io, $node, [], TreeStyle::minimal());

This outputs:

.. code-block:: terminal

    . config
    . . packages
    . . routes
    .   . framework.yaml
    .   . web_profiler.yaml
    . src
    . . Command
    . . Controller
    . . . DefaultController.php
    . . Kernel.php
    . templates
      . base.html.twig

**Rounded**::

    TreeHelper::createTree($io, $node, [], TreeStyle::rounded());

This outputs:

.. code-block:: terminal

    ├─ config
    │  ├─ packages
    │  ╰─ routes
    │     ├─ framework.yaml
    │     ╰─ web_profiler.yaml
    ├─ src
    │  ├─ Command
    │  ├─ Controller
    │  │  ╰─ DefaultController.php
    │  ╰─ Kernel.php
    ╰─ templates
       ╰─ base.html.twig

Making a Custom Tree Style
~~~~~~~~~~~~~~~~~~~~~~~~~~

You can create your own tree style by passing the characters to the constructor
of the :class:`Symfony\\Component\\Console\\Helper\\TreeStyle` class::

    use Symfony\Component\Console\Helper\TreeHelper;
    use Symfony\Component\Console\Helper\TreeStyle;

    $customStyle = new TreeStyle('🟣 ', '🟠 ', '🔵 ', '🟢 ', '🔴 ', '🟡 ');

    // Pass the custom style to the createTree method

    $tree = TreeHelper::createTree($io, null, [
        'src' =>  [
            'Command',
            'Controller' => [
                'DefaultController.php',
            ],
            'Kernel.php',
        ],
        'templates' => [
            'base.html.twig',
        ],
    ], $customStyle);

    $tree->render();

The above code will output the following tree:

.. code-block:: terminal

    🔵 🟣 🟡 src
    🔵 🟢 🟣 🟡 Command
    🔵 🟢 🟣 🟡 Controller
    🔵 🟢 🟢 🟠 🟡 DefaultController.php
    🔵 🟢 🟠 🟡 Kernel.php
    🔵 🟠 🟡 templates
    🔵 🔴 🟠 🟡 base.html.twig
