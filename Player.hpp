#ifndef __Player_hpp_2018_06_27_19_43
#define __Player_hpp_2018_06_27_19_43
#include <Base.hpp>
#include <vector>
#include <Random.hpp>
#include <Hash.hpp>
namespace tigame{
    class Item;
    class PlacedItem;
    class ItemStack{
    private:
        const Item* item;
        size_t quantity;
    public:
        ItemStack();
        ItemStack(const Item&,size_t quantity);
        ItemStack(const PlacedItem&);
        const Item& getItem()const;
        size_t getQuantity()const;
        void use(size_t);
        void add(size_t);
        int32_t hashCode()const;
    };

    class Bag{
    private:
        vector<ItemStack> items;
    public:
        Bag();
        Bag(const vector<ItemStack>&);
        template<size_t N> Bag(const ItemStack(&items)[N]){
            for(const ItemStack& t:items)
                this->items.push_back(t);
        }
        int32_t hashCode()const;
        void pickup(const ItemStack&);
        ItemStack& operator[](size_t);
        const ItemStack& operator[](size_t)const;
        void update();
        size_t getSize()const;

    };
    class Player{
    private:
        Vec2 position;
        double health;
        double hunger;
        double hydration;
        double exhaustion;
        Bag b;
        string name;
    public:
    };

}

#endif