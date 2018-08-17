#include "Tile.hpp"
#include "Text.hpp"
#include <Wrappers.hpp>
using namespace std::string_literals;
namespace tigame{
    class TileWater final:public Tile{
    public:
        TileWater(int id):Tile(id){}
        void printTo(Terminal& t,const PlacedTile&)const{
            constexpr Color blue{0x00239f};
            t.print(foreground<blue>,background<blue>," "s,Color::Reset);
        }
        virtual bool canMoveOnto(const PlacedTile&,Direction)const{
            return false;
        }
    };
    double getSlopeForPosition(const Vec2& v){
        return ((v*v)*8381393)%10000/100000.;
    }
    Direction getDirectionForPosition(const Vec2& v){
        return Direction{v.hashCode()*9304951%4};
    }
    class TilePond final:public Tile{
    public:
        TilePond(int id):Tile(id){}
        void printTo(Terminal& t,const PlacedTile&){
            constexpr Color darkBlue{0x00007f};
            constexpr Color cyan{0x007f8f};
            t.print(foreground<cyan>,background<darkBlue>,u8"•"s,Color::Reset);
        }
         virtual float getDamageFromMovingOnto(const PlacedTile& t,Random& r,Direction)const{
             if(r.nextDouble()<getSlopeForPosition(t.getPostion()))
                return std::numeric_limits<float>::infinity();
         }
    };
    class TileCliff final:public Tile{
    public:
        TileCliff(int id):Tile(id){}
        void printTo(Terminal& t,const PlacedTile&){
            constexpr Color brown{0xA0522D};
            t.print(foreground<Color::DARK_GRAY>,background<brown>,"^"s);
        }
        virtual float getDamageFromMovingOnto(const PlacedTile& t,Random& r,Direction)const{
            if(r.nextDouble()<getSlopeForPosition(t.getPostion()))
                return std::numeric_limits<float>::infinity();
        }
        virtual float getDamageFromMovingOff(const PlacedTile& t,Random&,Direction d)const override{
            if((~d)==getDirectionForPosition(t.getPostion()))
                return std::numeric_limits<float>::infinity();
        }
    };
    class TilePlain final:public Tile{
    public:
        TilePlain(int id):Tile(id){}
    };
    PolymorphicWrapper<Tile> tiles[] = {
        TileWater(0),
        TilePond(1),
        TileCliff(2)
    };
}