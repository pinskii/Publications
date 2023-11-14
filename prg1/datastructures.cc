// Datastructures.cc
//
// Student name: Pinja Rontu
// Student email: pinja.rontu@tuni.fi
// Student number: H299834

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <map>

#include <unordered_set>

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
    auto affiliation = allAffiliations.find(id);

    if (affiliation != allAffiliations.end()) {
        return affiliation->second.name;
    } else {
        return NO_NAME;
    }
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    auto affiliation = allAffiliations.find(id);

    if (affiliation != allAffiliations.end()) {
        return affiliation->second.coord;
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
    auto affiliation = allAffiliations.find(id);

        if (affiliation != allAffiliations.end()) {
            affiliation->second.coord = newcoord;
            return true;
        }

        return false;
}


bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
{
    if (allPublications.find(id) != allPublications.end()) {
            return false;
        }

    auto newPublication = Publication{
            id,
            name,
            year,
            affiliations,
            nullptr,
            {}
        };

    for (const auto& affiliationID : affiliations) {
         newPublication.affiliationIDs.push_back(affiliationID);
    }

    allPublications.emplace(id, newPublication);

    return true;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> publicationIDs;

    publicationIDs.reserve(allPublications.size());

    for (const auto& publication : allPublications) {
        publicationIDs.push_back(publication.first);
    }

    std::sort(publicationIDs.begin(), publicationIDs.end());

    return publicationIDs;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    auto publication = allPublications.find(id);

    if (publication != allPublications.end()) {
        return publication->second.title;
    }
    else {
        return NO_NAME;
    }
}

Year Datastructures::get_publication_year(PublicationID id)
{
    auto publication = allPublications.find(id);

    if (publication != allPublications.end()) {
        return publication->second.year;
    }
    else {
        return NO_YEAR;
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    auto publication = allPublications.find(id);

    if (publication != allPublications.end()) {
        return publication->second.affiliationIDs;
    }
    else {
        return {NO_AFFILIATION};
    }
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    auto child = allPublications.find(id);
    auto parent = allPublications.find(parentid);

    if (child != allPublications.end() && parent != allPublications.end()) {
        parent->second.references.push_back(std::make_shared<Publication>(child->second));
        child->second.parent = std::make_shared<Publication>(parent->second);
        return true;
    }
    else {
        return false;
    }
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    auto publication = allPublications.find(id);

    if (publication != allPublications.end()) {
        std::vector<PublicationID> directReferences;
        for (const auto& reference : publication->second.references) {
            directReferences.push_back(reference->id);
        }
        return directReferences;
    }
    else {
        return {NO_PUBLICATION};
    }
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    auto affiliation = allAffiliations.find(affiliationid);
    auto publication = allPublications.find(publicationid);

    if (affiliation != allAffiliations.end() && publication != allPublications.end()) {
        publication->second.affiliationIDs.push_back(affiliationid);
        affiliation->second.publicationIDs.push_back(publicationid);
        return true;
    }
    else {
        return false;
    }
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    auto affiliation = allAffiliations.find(id);

    if (affiliation != allAffiliations.end()) {
        return affiliation->second.publicationIDs;
    }
    else {
        return {NO_PUBLICATION};
    }
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    auto publication = allPublications.find(id);

    if (publication != allPublications.end()) {
        const auto& actualPublication = publication->second;

        if (actualPublication.parent) {
            return actualPublication.parent->id;
        }
        else {
            return NO_PUBLICATION;
        }
    }
    else {
        return NO_PUBLICATION;
    }
}

std::vector<std::pair<Year, PublicationID> > Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    auto affiliation = allAffiliations.find(affiliationid);

    if (affiliation != allAffiliations.end()) {
        const auto& publicationIDs = affiliation->second.publicationIDs;

        std::vector<std::pair<Year, PublicationID>> result;

        for (PublicationID publicationID : publicationIDs) {
            auto publication = allPublications.find(publicationID);

            if (publication != allPublications.end() && publication->second.year >= year) {
                result.emplace_back(publication->second.year, publicationID);
            }
        }

        std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
            return (a.first < b.first) || (a.first == b.first && a.second < b.second);
        });

        return result;
    }
    else {
        return {{NO_YEAR, NO_PUBLICATION}};
    }
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    auto publication = allPublications.find(id);

   if (publication != allPublications.end()) {
       std::unordered_set<PublicationID> visited;
       std::vector<PublicationID> result;

       // Function for preorder traversal
       std::function<void(const std::shared_ptr<Publication>)> traversing_tree =
           [&](const std::shared_ptr<Publication> currentPublication) {

               if (currentPublication->parent &&
                       visited.find(currentPublication->parent->id) == visited.end()) {

                   visited.insert(currentPublication->parent->id);
                   result.push_back(currentPublication->parent->id);
                   traversing_tree(currentPublication->parent);
               }
           };

       // Start traversal again from the next publication
       traversing_tree(std::make_shared<Publication>(publication->second));

       return result;
   }
   else {
       return {NO_PUBLICATION};
   }
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


