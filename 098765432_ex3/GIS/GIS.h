#pragma once

#include "../Common/GISNamedTypes.h"
#include "../Common/Restrictions.h"
#include "../Common/AbstractGIS.h"
#include "../Common/AbstractWay.h"
#include <string>
#include <vector> 
#include <tuple> 
#include <optional>

/**
 * @brief GIS_098765432 class 
 * 
 */
class GIS_098765432 : public AbstractGIS {

	/* ... Your Private implimentation may go here ... */

public:	
	/**
	 * @brief Loads a map file
	 * 
	 * 	[1] in case the system had existing data, the data loaded from file is added to the existing data
	 *  [2] in case entityId from file exists already the old data related to this id is replaced with the new data RELAXED: may be reject - proper error should be logged to errors.log
	 *  [3] in case an entity in file doesn't have an Id, a new Id would be generated for it automatically
	 * 
	 * @param filename - Provided mapfile
	 * @return std::vector<EntityId> - A vector of all the EntityIds that were loaded (either Ids that appeared in file or generated) in the exact order the objects appeared in the file
	 */
	std::vector<EntityId> loadMapFile(const std::string& filename) override;
	
	/**
	 * @brief The function shall get EntityId of a Junction and return a vector of Ids of all the ways that start at this junction and those which end at this junction and are bidirectional. 
	 *        If the given Id is not known or is not of a junction the function shall return an empty vector (you may log an error).
	 * 
	 * @param junctionId 
	 * @return std::vector<EntityId> - A vector of Ids of all the Ways that start at given junction (also bidirectional Ways which end at this junction).
	 */
	std::vector<EntityId> getWaysByJunction(const EntityId& junctionId) const override;

	/**
	 * @brief Get the closest point along a Way that is closest to Referenced Point and the EntityId of that Way
	 * 
	 * @param c - Referenced Point 
	 * @return std::pair<Coordinates, EntityId> - The Coordinates of closest point along a Way that is closest to Referenced Point and the EntityId of that Way
	 */
	std::tuple<Coordinates, EntityId, std::size_t> getWayClosestPoint(const Coordinates& c) const override;

	/**
	 * @brief Get the closest point to Referenced Point, along a Way that complies with provided Restrictions and the EntityId of that Way
	 *        Restrictions can be provided as: Restrictions("highway") means avoid highway, Restrictions(" toll ") means avoid toll, Restrictions("highway , toll  ") or Restrictions("toll,highway") both mean avoid highway and toll, etc.
	 * 
	 * @param c - Referenced Point
	 * @param res - Restrictions
	 * @return std::pair<Coordinates, EntityId> - The closest point to Referenced Point, along a Way that complies with provided Restrictions and the EntityId of that Way
	 */
	std::tuple<Coordinates, EntityId, std::size_t> getWayClosestPoint(const Coordinates& c, const Restrictions& res) const;

	/**
	 * @brief Get the Way object et EntityId of a Way and return the Way itself. 
	 *        In case the id does not represent a valid way throw an exception of your choice.
	 * 
	 * @param wayId - ID of Way
	 * @return const Way& 
	 */
	const AbstractWay& getWay(const EntityId& wayId) const override;
};
