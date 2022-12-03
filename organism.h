#ifndef ORGANISM_H
#define ORGANISM_H

#include <bits/stdc++.h>


// static_assert(std::is_equality_comparable());
template <typename species_t, bool can_eat_meat, bool can_eat_plants>
class Organism {
private:
    /* data */
    species_t species;
    uint64_t vitality;
protected:
    Organism(species_t const &species, uint64_t vitality)
        : species(species)
        , vitality(vitality){}
    ~Organism(){};
public:
    uint64_t get_vitality(){
        return vitality;
    }
    const species_t &get_species(){
        return species;
    }
};

// Organism::Organism(species_t const &species, uint64_t vitality){
    
// }

#endif