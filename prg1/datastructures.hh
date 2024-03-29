// Datastructures.hh
//
// Student name: Pinja Rontu
// Student email: pinja.rontu@tuni.fi
// Student number: H299834

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <memory>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: time complexity of size()
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of clear()
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: O(n) for for loop and O(1) for push_back()
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(1)
    // Short rationale for estimate: time complexity for find() and inserting one
    // element for unordered maps
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: O(n) for for loops and O(log(n))
    // for multimap insert() and O(1) for push_back()
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: O(n) for for loops and O(log(n))
    // for multimap insert() and O(1) for push_back()
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: O(n) for for loop
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: O(1) for find, O(n) for for loop,
    // O(1) average O(n) worst case for emplace()
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: O(n) for for loop, O(1) for push_back(),
    // O(n log(n)) for sort()
    std::vector<PublicationID> all_publications();

    // Estimate of performance: average O(1), worst case O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    Name get_publication_name(PublicationID id);

    // Estimate of performance: average O(1), worst case O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: average O(1) worst case O(n) for unordered map,
    // O(n) for for loop, O(1) for push_back()
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    // and for push_back()
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: average O(1), worst case O(n)
    // Short rationale for estimate: time complexity of find() for unordered map
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n log(n))
    // Short rationale for estimate: average O(1) for find(), O(n) for for loop,
    // O(1) for emplace_back(), O(n log(n)) for sort()
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n)
    // Short rationale for estimate: average O(1) worst case O(n) for insert(),
    // average O(1) worst case O(n) for find(), O(1) for push_back()
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_publication(PublicationID publicationid);


private:

    struct Affiliation {
        AffiliationID id;
        Name name;
        Coord coord;
        std::vector<PublicationID> publicationIDs; // which publications are under this affiliation
    };

    std::unordered_map<AffiliationID, Affiliation> allAffiliations;

    struct Publication {
        PublicationID id;
        Name title;
        Year year;
        std::vector<AffiliationID> affiliationIDs; // which affiliations own this publication
        std::shared_ptr<Publication> parent; // which publication is this publication referenced by
        std::vector<std::shared_ptr<Publication>> references; // which publications is this publication referencing
    };

    std::unordered_map<PublicationID, Publication> allPublications;

};

#endif // DATASTRUCTURES_HH
