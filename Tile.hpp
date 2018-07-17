#ifndef __Tile_hpp_2018_06_27_17_21
#define __Tile_hpp_2018_06_27_17_21

#include <vector>
#include <string>
#include <Random.hpp>
#include <Base.hpp>

using std::string;
namespace tigame{
    class PlacedTile;
    class Player;
    class Item;
    class PlacementData;
    


    class Tile{
    private:
        int tileId;
    protected:
        Tile(int);
        Tile();
    public:
        virtual ~Tile();
        virtual bool isSpecialTile()const;
        virtual bool isTreasureTile()const;
        virtual string getName()const=0;
        virtual string getDescription1(const PlacedTile&)const=0;
        virtual string getDescription2(const PlacedTile&)const;
        virtual bool canInteractWith(const PlacedTile&)const;
        virtual bool canMoveOnto(const PlacedTile&,Direction)const;
        virtual float getDamageFromMovingOnto(const PlacedTile&,Direction)const;
        virtual float getDamageFromMovingOff(const PlacedTile&,Direction)const;
        int getId()const;
        virtual void generate(Random&,PlacedTile&)const;
        int32_t hashCode()const;
    };
    
     
    class PlacedItem{
    private:
        const Item* item;
        size_t quantity;
        Vec2 position;
    public:
        PlacedItem();
        PlacedItem(const Item&,int,const Vec2&);
        PlacedItem(const Vec2&,Random&);
        const Vec2& getPosition()const;
        const Item& getItem()const;
        int getQuantity()const;
        void pickup(const Player&);
        int32_t hashCode()const;
    };
    

    class PlacedTile{
    private:
        const Tile* tile;
        PlacedItem item;
        Direction facing;
        double slope;
        Vec2 position;
    public:
        PlacedTile(const Tile&,const PlacedItem&,const Vec2&);
        PlacedTile(const Tile&,const PlacedItem&,const Vec2&,double);
        PlacedTile(const Tile&,const PlacedItem&,const Vec2&,Direction,double);
        PlacedTile(const Vec2&,Random&,const PlacementData&);
        const Vec2& getPostion()const;
        const PlacedItem& getPlacedItem()const;
        Direction getFacingDirection()const;
        void setFacingDirection(Direction);
        void setSlope(double);
        const Tile& getTile()const;
        double getSlope()const;
        bool enterTile(Direction,Player&,Random&)const;
        int32_t hashCode()const;
    };
    
}

int32_t hashcode(const tigame::Tile&);
int32_t hashcode(const tigame::PlacedTile&);
int32_t hashcode(const tigame::PlacedItem&);

namespace std{
    template<> struct hash<tigame::Tile>{
        constexpr hash()=default;
        size_t operator()(const tigame::Tile&)const;
    };
    template<> struct hash<tigame::PlacedItem>{
        constexpr hash()=default;
        size_t operator()(const tigame::Tile&)const;
    };
    template<> struct hash<tigame::PlacedTile>{
        constexpr hash()=default;
        size_t operator()(const tigame::PlacedTile&)const;
    };
}

#endif