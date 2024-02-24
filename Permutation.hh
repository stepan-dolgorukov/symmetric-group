template< typename Element,
          auto set,
          template< typename, typename > typename Map >
class Permutation
{
private:
  Map< Element, Element > m;

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
    }
  }
};
