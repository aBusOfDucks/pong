#ifndef __BUSH_H__
#define __BUSH_H__

#include "plant.h"
#include <mutex>

class bush : public plant{
private:
    int bitmap_no_berries;
    int bitmap_no_berries_on_fire;


    std::mutex mutex_berries;
    bool has_berries;
    int berries_respawn_time;
    int berries_time_to_respawn;

    void loose_berries()
    {
        has_berries = false;
        berries_time_to_respawn = berries_respawn_time;
        if(is_on_fire)
        {
            bitmap_index = bitmap_no_berries_on_fire;
        }
        else
        {
            bitmap_index = bitmap_no_berries;
        }
    }
    void get_berries()
    {
        has_berries = true;
        if(is_on_fire)
        {
            bitmap_index = bitmap_on_fire_index;
        }
        else
        {
            bitmap_index = bitmap_default;
        }
    }
public:

    int entity_interaction(int code) override
    {
        if(code == ENTITY_CODE_DOES_HAVE_BERRIES)
        {
            std::unique_lock<std::mutex> lock(mutex_berries);
            if(has_berries)
                return ENTITY_ANS_HAS_BERRIES;
            else
                return ENTITY_ANS_DOES_NOT_HAVE_BERRIES;
        }
        return ENTITY_ANS_NONE;
    }

    bush(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_BUSH_INDEX;
        bitmap_on_fire_index = BITMAP_BUSH_ON_FIRE_INDEX;
        time_to_burn = BUSH_TIME_TO_BURN;
        bitmap_no_berries = BITMAP_BUSH_NO_BERRIES_INDEX;
        bitmap_no_berries_on_fire = BITMAP_BUSH_NO_BERRIES_ON_FIRE_INDEX;
        berries_respawn_time = BUSH_BERRIES_RESPAWN_TIME;
        has_berries = true;
        entity_type = BUSH_TYPE;
        plant::init(x, y, bitmaps);
    }

    void hit_by(int type) override
    {
        if(type == FIRE_PROJECTILE_TYPE)
        {
            if (is_on_fire)
                kill();
            else
            {
                is_on_fire = true;
                std::unique_lock<std::mutex> lock(mutex_berries);
                if(has_berries)
                    bitmap_index = bitmap_on_fire_index;
                else
                    bitmap_index = bitmap_no_berries_on_fire;
            }
        }
        if(type == MAGIC_PROJECTILE_TYPE)
        {
            if(is_on_fire)
            {
                is_on_fire = false;
                bitmap_index = bitmap_default;
                time_to_burn = time_to_burn_default;
            }
            std::unique_lock<std::mutex> lock(mutex_berries);
            if(!has_berries)
            {
                get_berries();
            }
        }
        if(type == DEATH_PROJECTILE_TYPE)
            kill();
    }

    bool entity_collide(entity * e) override
    {
        bool ans = entity::entity_collide(e);
        std::unique_lock<std::mutex> lock(mutex_berries);
        if(ans)
            if(e->get_type() == PLAYER_TYPE)
                loose_berries();
        if(ans)
        {
            if(e->get_type() == PIG_TYPE)
            {
                if(has_berries)
                    e->entity_interaction(ENTITY_CODE_EAT_BERRIES);
                loose_berries();
            }
        }
        return ans;
    }

    bool collide(coordinate left_upper, coordinate right_bottom, int type) override
    {
        bool ans = entity::collide(left_upper, right_bottom, type);
        std::unique_lock<std::mutex> lock(mutex_berries);
        if(ans)
            if(type == PIG_TYPE)
            {
                loose_berries();
            }
        if(ans)
        {
            if(type == PLAYER_TYPE)
            {
                loose_berries();
            }
        }
        return ans;
    }

    void move(entity ** entities, entity * player) override
    {
        if (exist)
        {
            std::unique_lock<std::mutex> lock(mutex_berries);
            if(berries_time_to_respawn <= 0 && !has_berries)
                get_berries();
            else
            {
                if(!has_berries)
                    berries_time_to_respawn--;
            }
        }
        plant::move(entities, player);
    }
};

#endif //__BUSH_H__
