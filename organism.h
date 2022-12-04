#ifndef ORGANISM_H
#define ORGANISM_H

#include <bits/stdc++.h>


template <typename species_t, bool can_eat_meat, bool can_eat_plants>
requires std::equality_comparable<species_t>
    class Organism {
    private:
        species_t species;
        uint64_t vitality;
        bool eats_meat, eats_plants;
    public:
        constexpr Organism(species_t const &species, uint64_t vitality)
            : species(species)
            ,  vitality(vitality)
            , eats_meat(can_eat_meat)
            , eats_plants(can_eat_plants){}

        uint64_t get_vitality(){
            return vitality;
        }
        const species_t &get_species(){
            return species;
        }
   
        constexpr bool is_plant(){
            return !can_eat_meat && !can_eat_plants;
        }
    };

template <typename species_t>
    using Carnivore = Organism<species_t, true, false>;
template <typename species_t>
    using Omnivore = Organism<species_t, true, true>;
template <typename species_t>
    using Herbivore = Organism<species_t, false, true>;
template <typename species_t>
    using Plant = Organism<species_t, false, false>;



template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p>
    constexpr bool same_species(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
              Organism<species_t, sp2_eats_m, sp2_eats_p> organism2){
        return organism1.get_species() == organism2.get_species() && 
            sp1_eats_p == sp2_eats_p &&
            sp2_eats_m == sp2_eats_m;
    }

template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p> //does this needs to reapeted?
    constexpr std::tuple<Organism<species_t, sp1_eats_m, sp1_eats_p>,
                         Organism<species_t, sp2_eats_m, sp2_eats_p>,
                         std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
    encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
              Organism<species_t, sp2_eats_m, sp2_eats_p> organism2){
                static_assert(!(organism1.is_plant() && organism2.is_plant()) ,"plants don't move");

                return std::make_tuple(organism1, organism2, organism1 );
              }

#endif