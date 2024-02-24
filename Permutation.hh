#include <set>
#include <utility>

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

  bool without_repeating_elements(  )
  {
    std::set< Element > s;

    for( auto element : set )
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

public:
  Permutation(  )
  {
    assert( without_repeating_elements(  ) );

    for( Element element : set )
    {
      m[ element ] = element;
    }
  }

  Permutation( std::initializer_list<
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
  }

  Element operator()( Element q )
  {
    assert( element_of_set( q ) );

    return m.at( q );
  }
};
