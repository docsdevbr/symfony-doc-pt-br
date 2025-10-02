The TypeInfo Component
======================

The TypeInfo component extracts type information from PHP elements like properties,
arguments and return types.

This component provides:

* A powerful ``Type`` definition that can handle unions, intersections, and generics
  (and can be extended to support more types in the future);
* A way to get types from PHP elements such as properties, method arguments,
  return types, and raw strings.

Installation
------------

.. code-block:: terminal

    $ composer require symfony/type-info

.. include:: /components/require_autoload.rst.inc

Usage
-----

This component gives you a :class:`Symfony\\Component\\TypeInfo\\Type` object that
represents the PHP type of anything you built or asked to resolve.

There are two ways to use this component. First one is to create a type manually thanks
to the :class:`Symfony\\Component\\TypeInfo\\Type` static methods as following::

    use Symfony\Component\TypeInfo\Type;

    Type::int();
    Type::nullable(Type::string());
    Type::generic(Type::object(Collection::class), Type::int());
    Type::list(Type::bool());
    Type::intersection(Type::object(\Stringable::class), Type::object(\Iterator::class));

Many others methods are available and can be found
in :class:`Symfony\\Component\\TypeInfo\\TypeFactoryTrait`.

You can also use a generic method that detects the type automatically::

    Type::fromValue(1.1);   // same as Type::float()
    Type::fromValue('...'); // same as Type::string()
    Type::fromValue(false); // same as Type::false()

Resolvers
~~~~~~~~~

The second way to use the component is by using ``TypeInfo`` to resolve a type
based on reflection or a simple string. This approach is designed for libraries
that need a simple way to describe a class or anything with a type::

    use Symfony\Component\TypeInfo\Type;
    use Symfony\Component\TypeInfo\TypeResolver\TypeResolver;

    class Dummy
    {
        public function __construct(
            public int $id,
        ) {
        }
    }

    // Instantiate a new resolver
    $typeResolver = TypeResolver::create();

    // Then resolve types for any subject
    $typeResolver->resolve(new \ReflectionProperty(Dummy::class, 'id')); // returns an "int" Type instance
    $typeResolver->resolve('bool'); // returns a "bool" Type instance

    // Types can be instantiated thanks to static factories
    $type = Type::list(Type::nullable(Type::bool()));

    // Type instances have several helper methods

    // for collections, it returns the type of the item used as the key;
    // in this example, the collection is a list, so it returns an "int" Type instance
    $keyType = $type->getCollectionKeyType();

    // you can chain the utility methods (e.g. to introspect the values of the collection)
    // the following code will return true
    $isValueNullable = $type->getCollectionValueType()->isNullable();

Each of these calls will return you a ``Type`` instance that corresponds to the
static method used. You can also resolve types from a string (as shown in the
``bool`` parameter of the previous example)

PHPDoc Parsing
~~~~~~~~~~~~~~

In many cases, you may not have cleanly typed properties or may need more precise
type definitions provided by advanced PHPDoc. To achieve this, you can use a string
resolver based on the PHPDoc annotations.

First, run the command ``composer require phpstan/phpdoc-parser`` to install the
PHP package required for string resolving. Then, follow these steps::

    use Symfony\Component\TypeInfo\TypeResolver\TypeResolver;

    class Dummy
    {
        public function __construct(
            public int $id,
            /** @var string[] $tags */
            public array $tags,
        ) {
        }
    }

    $typeResolver = TypeResolver::create();
    $typeResolver->resolve(new \ReflectionProperty(Dummy::class, 'id')); // returns an "int" Type
    $typeResolver->resolve(new \ReflectionProperty(Dummy::class, 'tags')); // returns a collection with "int" as key and "string" as values Type

Advanced Usages
~~~~~~~~~~~~~~~

The TypeInfo component provides various methods to manipulate and check types,
depending on your needs.

**Identify** a type::

    // define a simple integer type
    $type = Type::int();
    // check if the type matches a specific identifier
    $type->isIdentifiedBy(TypeIdentifier::INT);    // true
    $type->isIdentifiedBy(TypeIdentifier::STRING); // false

    // define a union type (equivalent to PHP's int|string)
    $type = Type::union(Type::string(), Type::int());
    // now the second check is true because the union type contains the string type
    $type->isIdentifiedBy(TypeIdentifier::INT);    // true
    $type->isIdentifiedBy(TypeIdentifier::STRING); // true

    class DummyParent {}
    class Dummy extends DummyParent implements DummyInterface {}

    // define an object type
    $type = Type::object(Dummy::class);

    // check if the type is an object or matches a specific class
    $type->isIdentifiedBy(TypeIdentifier::OBJECT); // true
    $type->isIdentifiedBy(Dummy::class);           // true
    // check if it inherits/implements something
    $type->isIdentifiedBy(DummyParent::class);     // true
    $type->isIdentifiedBy(DummyInterface::class);  // true

Checking if a type **accepts a value**::

    $type = Type::int();
    // check if the type accepts a given value
    $type->accepts(123); // true
    $type->accepts('z'); // false

    $type = Type::union(Type::string(), Type::int());
    // now the second check is true because the union type accepts either an int or a string value
    $type->accepts(123); // true
    $type->accepts('z'); // true

Using callables for **complex checks**::

    class Foo
    {
        private int $integer;
        private string $string;
        private ?float $float;
    }

    $reflClass = new \ReflectionClass(Foo::class);

    $resolver = TypeResolver::create();
    $integerType = $resolver->resolve($reflClass->getProperty('integer'));
    $stringType = $resolver->resolve($reflClass->getProperty('string'));
    $floatType = $resolver->resolve($reflClass->getProperty('float'));

    // define a callable to validate non-nullable number types
    $isNonNullableNumber = function (Type $type): bool {
        if ($type->isNullable()) {
            return false;
        }

        if ($type->isIdentifiedBy(TypeIdentifier::INT) || $type->isIdentifiedBy(TypeIdentifier::FLOAT)) {
            return true;
        }

        return false;
    };

    $integerType->isSatisfiedBy($isNonNullableNumber); // true
    $stringType->isSatisfiedBy($isNonNullableNumber);  // false
    $floatType->isSatisfiedBy($isNonNullableNumber);   // false
