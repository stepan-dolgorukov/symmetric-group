template< typename Element,
          auto set,
          template< typename, typename > typename Map >
class Permutation
{
private:
  decltype( set ) s = set;
  Map< Element, Element > m;

  bool element_of_set( Element q )
  {
    for( auto element : set )
    {
      if( q == element )
      {
        return true;
      }
    }

    return false;
  }

public:
  Permutation(  )
  {
    for( Element element : set )
    {
      m[ element ] = element;
    }
  }

  Permutation( Map< Element, Element > map ) : Permutation(  )
  {
    for( auto [ source, destination ] : map )
    {
      m[ source ] = destination;

      assert( element_of_set( source ) &&
              element_of_set( destination ) );
    }
  }
};
