#ifndef ORGANISM_H
#define ORGANISM_H

#include <bits/stdc++.h>


template <typename species_t, bool can_eat_meat, bool can_eat_plants>
requires std::equality_comparable<species_t>
    class Organism {
    private:
        species_t species;
        uint64_t vitality;
    public:
        constexpr Organism(species_t const &species, uint64_t vitality)
            : species(species)
            ,  vitality(vitality){}

        constexpr Organism copy (uint64_t new_vitality) const{
            return Organism<species_t, can_eat_meat, can_eat_plants>(species, new_vitality); 
        }

        constexpr uint64_t get_vitality() const {
            return vitality;
        }
        constexpr const species_t &get_species() const{
            return species;
        }
   
        constexpr bool is_plant() const{
            return !can_eat_meat && !can_eat_plants;
        }
        constexpr bool is_dead() const{
            return vitality == 0;
        }
        

        template < bool m,bool  p>
         constexpr bool can_eat(Organism<species_t,m,p> other) const{
            if(can_eat_plants && other.is_plant()) return true;
            if(can_eat_meat && !other.is_plant()) return true;
            return false;
        }
        
        template < bool m,bool  p>
        constexpr Organism eats(Organism<species_t,m,p> other) const{
            return copy(vitality + other.get_vitality()/2);
        }
        //is it possible without tamplate just Organism<species_t,false,false> ?
        template < bool m,bool  p>
        constexpr Organism consumesPlant(Organism<species_t,m,p> other) const{
            return copy(vitality + other.get_vitality());
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
    fight(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
              Organism<species_t, sp2_eats_m, sp2_eats_p> organism2){
        uint64_t vitality1 = organism1.get_vitality();
        species_t spec1 = organism1.get_species();
        uint64_t vitality2 = organism2.get_vitality();
        species_t spec2 = organism2.get_species();
        if(vitality1 == vitality2){
            return std::make_tuple(organism1.copy(0), organism2.copy(0), std::nullopt);
        } else if(vitality1 > vitality2 ){
            return std::make_tuple(organism1.eats(organism2), organism2.copy(0), std::nullopt);
        }
        return std::make_tuple(organism1.copy(0), organism2.eats(organism1), std::nullopt);
    }

template <typename species_t, bool sp1_eats_m, bool sp1_eats_p, bool sp2_eats_m, bool sp2_eats_p> //does this needs to reapeted?
    constexpr std::tuple<Organism<species_t, sp1_eats_m, sp1_eats_p>,
                         Organism<species_t, sp2_eats_m, sp2_eats_p>,
                         std::optional<Organism<species_t, sp1_eats_m, sp1_eats_p>>>
    encounter(Organism<species_t, sp1_eats_m, sp1_eats_p> organism1,
              Organism<species_t, sp2_eats_m, sp2_eats_p> organism2){
                // 2.
                static_assert(!(organism1.is_plant() && organism2.is_plant()) ,"plants don't move");

                //3.1
                if( !organism1.is_dead() && !organism2.is_dead() ){
                
                    //4.
                    if(same_species(organism1, organism2)){
                        uint64_t vitality = (organism1.get_vitality()+organism2.get_vitality())/2;
                        return std::make_tuple(organism1, organism2, Organism<species_t,sp1_eats_m,sp1_eats_p>(organism1.get_species(),vitality));
                    }

                    //6.
                    if(organism1.can_eat(organism2) && organism2.can_eat(organism1) ){
                        return fight(organism1,organism2);
                    }

                    //7. 
                    if(organism2.is_plant() && organism1.can_eat(organism2)){
                        return std::make_tuple(organism1.consumesPlant(organism2),organism2.copy(0), std::nullopt);
                    }
                    if(organism1.is_plant() && organism2.can_eat(organism1)){
                        return std::make_tuple(organism1.copy(0),organism2.consumesPlant(organism1), std::nullopt);
                    }

                    //8.
                    if(organism1.can_eat(organism2) && organism1.get_vitality() > organism2.get_vitality()){
                        return std::make_tuple(organism1.eats(organism2), organism2.copy(0), std::nullopt);
                    }
                    if(organism2.can_eat(organism1) && organism2.get_vitality() > organism1.get_vitality()){
                        return std::make_tuple(organism1.copy(0), organism2.eats(organism1), std::nullopt);
                    }


                }
                //3.2 and  5.
                return std::make_tuple(organism1, organism2, std::nullopt);
              }

#endif