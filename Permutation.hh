#include <set>
#include <utility>

template< typename Element,
          auto set,
          template< typename, typename > typename Map >
class Permutation
{
private:
  Map< Element, Element > m;

  bool element_of_set( Element q )
  {
    for( Element element : set )
    {
      if( q == element )
      {
        return true;
      }
    }

    return false;
  }

  bool without_repeating_elements(  )
  {
    for( std::set< Element > s;
         auto element : set )
    {
      if( 1u == s.count( element ) )
      {
        return false;
      }

      s.insert( element );
    }

    return true;
  }

  bool injectiveness(  )
  {
    for( std::set< Element > destinations;
         Element element : set )
    {
      if( false == destinations.insert( operator()( element ) ).second )
      {
        return false;
      }
    }

    return true;
  }

  bool surjectiveness(  )
  {
    std::set< Element > destinations;

    for( Element element : set )
    {
      destinations.insert( operator()( element ) );
    }

    return set.size(  ) == destinations.size(  );
  }

public:
  Permutation(  )
  {
    assert( without_repeating_elements(  ) );

    for( Element element : set )
    {
      m[ element ] = element;
    }
  }

  Permutation( std::vector<
                            std::pair<
                                       Element,
                                       Element  >
                                                  > transitions )
  : Permutation(  )
  {
    for( std::set< Element > sources,
                             destinations;
         auto [ source, destination ] : transitions )
    {
      assert( true == sources.insert( source ).second );
      assert( true == destinations.insert( destination ).second );
    }

    for( auto [ source, destination ] : transitions )
    {
      m[ source ] = destination;

      assert( element_of_set( source ) &&
              element_of_set( destination ) );
    }

    assert( true == injectiveness(  ) &&
            true == surjectiveness(  ) );
  }

  Element operator()( const Element q )
  {
    assert( element_of_set( q ) );

    return m.at( q );
  }
};
