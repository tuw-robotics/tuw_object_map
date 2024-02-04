#ifndef TUW_OBJECT_MAP__GEO_MAP_HPP_
#define TUW_OBJECT_MAP__GEO_MAP_HPP_

#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>

namespace tuw_object_map
{
    class GeoMapMetaData
    {
    public:
        GeoMapMetaData();
        double resolution;          /// The map resolution [m/cell]
        cv::Size size;              /// Map size width and height [cells]
        cv::Vec2d origin;           /// The origin of the map [m, m, rad].  This is the real-world pose of the cell (0,0) in the map.
        double rotation;            /// The origin of the map [m, m, rad].  This is the real-world pose of the cell (0,0) in the map.
        /*
        * inti all meta data and transformation matrix
        * @param latitude
        * @param longitude
        * @param altitude
        * @param overwrite_map_orgin on true it moves the map orition form cell (0,0) into the map center
        */
        void init(double latitude, double longitude, double altitude, bool overwrite_map_orgin = false);
        /*
        * inti all meta data and transformation matrix
        * @param utm_easting
        * @param utm_northing
        * @param altitude
        * @param utm_zone
        * @param utm_northp
        * @param overwrite_map_orgin on true it moves the map orition form cell (0,0) into the map center
        */
        void init(double utm_easting, double utm_northing, double altitude, int utm_zone, bool utm_northp, bool overwrite_map_orgin);

        std::string info_map() const;
        std::string info_geo() const;
        double dx() const;
        double dy() const;
        cv::Vec3d &lla2utm(const cv::Vec3d &src, cv::Vec3d &des ) const;
        cv::Vec3d lla2utm(const cv::Vec3d &src) const;
        cv::Vec3d &utm2world(const cv::Vec3d &src, cv::Vec3d &des ) const;
        cv::Vec3d utm2world(const cv::Vec3d &src) const;
        cv::Vec2d &world2map(const cv::Vec3d &src, cv::Vec2d &des ) const;
        cv::Vec2d world2map(const cv::Vec3d &src) const;
        cv::Vec2d &world2map(const cv::Vec2d &src, cv::Vec2d &des ) const;
        cv::Vec2d world2map(const cv::Vec2d &src) const;
        cv::Point &g2m(const cv::Vec3d &src, cv::Point &des) const;          /// latitude, longitude, altitude to map [pix]
        cv::Point g2m(cv::Vec3d &src) const;                                 /// latitude, longitude, altitude to map [pix]

        cv::Vec3d &map2world(const cv::Vec2d &src, cv::Vec3d &des ) const;
        cv::Vec2d &map2world(const cv::Vec2d &src, cv::Vec2d &des ) const;
        cv::Vec2d map2world(const cv::Vec2d &src) const;
        cv::Vec3d &world2utm(const cv::Vec3d &src, cv::Vec3d &des ) const;
        cv::Vec3d world2utm(const cv::Vec3d &src) const;
        cv::Vec3d &utm2lla(const cv::Vec3d &src, cv::Vec3d &des ) const;
        cv::Vec3d utm2lla(const cv::Vec3d &src) const;
        cv::Vec3d &m2g(const cv::Vec2d &src, cv::Vec3d &des) const;          /// map [pix] to latitude, longitude, altitude
        cv::Vec3d &m2g(const cv::Point &src, cv::Vec3d &des) const;          /// map [pix] to latitude, longitude, altitude
        cv::Vec3d m2g(const cv::Point &src) const;                           /// map [pix] to latitude, longitude, altitude
    private:
        cv::Vec3d origin_world_utm;
        int utm_zone;
        bool utm_northp;
        cv::Matx33d Mw2m;
        cv::Matx33d Mm2w;
    };

    class GeoMap
    {
    public:
        GeoMap();
        void init(const GeoMapMetaData &info);
    };

}
#endif // TUW_OBJECT_MAP__GEO_MAP_HPP_
