// Datastructures.cc
//
// Student name: Pinja Rontu
// Student email: pinja.rontu@tuni.fi
// Student number: H299834

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <map>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return allAffiliations.size();
}

void Datastructures::clear_all()
{
    allAffiliations.clear();
    allPublications.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    std::vector<AffiliationID> affiliations;

    for (auto& affiliation : allAffiliations) {
        affiliations.push_back(affiliation.first);
    }

    return affiliations;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    if (allAffiliations.find(id) != allAffiliations.end()) {
            return false;
        }

    else {
        Affiliation newAffiliation;
        newAffiliation.id = id;
        newAffiliation.name = name;
        newAffiliation.coord = xy;

        allAffiliations[id] = newAffiliation;

        return true;
    }
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    auto it = allAffiliations.find(id);

    if (it != allAffiliations.end()) {
        return it->second.name;
    } else {
        return NO_NAME;
    }
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    auto it = allAffiliations.find(id);

    if (it != allAffiliations.end()) {
        return it->second.coord;
    } else {
        return NO_COORD;
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    std::multimap<Name, AffiliationID> affiliation_map;
        std::vector<AffiliationID> affiliation_vector;

        for (const auto& affiliation : allAffiliations) {
            affiliation_map.insert({affiliation.second.name, affiliation.first});
        }

        for (const auto& affiliation : affiliation_map) {
            affiliation_vector.push_back(affiliation.second);
        }

        return affiliation_vector;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::multimap<int, AffiliationID> affiliation_map;
        std::vector<AffiliationID> affiliation_vector;
        unsigned int distance = 0;

        for (const auto& affiliation : allAffiliations) {
            distance=sqrt(pow(affiliation.second.coord.x, 2)
                                  +pow(affiliation.second.coord.y, 2));
            affiliation_map.insert({distance, affiliation.first});
        }

        for (const auto& affiliation : affiliation_map) {
            affiliation_vector.push_back(affiliation.second);
        }

        return affiliation_vector;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    for (const auto& affiliation : allAffiliations) {
            if (affiliation.second.coord.x == xy.x && affiliation.second.coord.y == xy.y) {
                return affiliation.first;
            }
        }

        return NO_AFFILIATION;
}
bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto it = allAffiliations.find(id);

        if (it != allAffiliations.end()) {
            it->second.coord = newcoord;
            return true;
        }

        return false;
}


bool Datastructures::add_publication(PublicationID /*id*/, const Name &/*name*/, Year /*year*/, const std::vector<AffiliationID> &/*affiliations*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("add_publication()");
}

std::vector<PublicationID> Datastructures::all_publications()
{
    // Replace the line below with your implementation
    throw NotImplemented("all_publications()");
}

Name Datastructures::get_publication_name(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publication_name()");
}

Year Datastructures::get_publication_year(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publication_year()");
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations()");
}

bool Datastructures::add_reference(PublicationID /*id*/, PublicationID /*parentid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("add_reference()");
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_direct_references()");
}

bool Datastructures::add_affiliation_to_publication(AffiliationID /*affiliationid*/, PublicationID /*publicationid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("add_affiliation_to_publication()");
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publications()");
}

PublicationID Datastructures::get_parent(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_parent()");
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID /*affiliationid*/, Year /*year*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_publications_after()");
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_referenced_by_chain()");
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_all_references()");
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_affiliations_closest_to()");
}

bool Datastructures::remove_affiliation(AffiliationID /*id*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_affiliation()");
}

PublicationID Datastructures::get_closest_common_parent(PublicationID /*id1*/, PublicationID /*id2*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_closest_common_parent()");
}

bool Datastructures::remove_publication(PublicationID /*publicationid*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("remove_publication()");
}


