#ifndef ACTIVE_3D_PLANNING_VOXBLOX_MAP_VOXBLOX_H
#define ACTIVE_3D_PLANNING_VOXBLOX_MAP_VOXBLOX_H

#include "active_3d_planning_core/map/tsdf_map.h"
#include <active_3d_planning_core/module/module_factory_registry.h>

#include <voxblox_ros/esdf_server.h>

#include <memory>

namespace active_3d_planning {
    namespace map {

        // Voxblox as a map representation
        class VoxbloxMap : public TSDFMap {
        public:
            VoxbloxMap(PlannerI &planner);

            // implement virtual methods
            void setupFromParamMap(Module::ParamMap *param_map) override;

            // check collision for a single pose
            virtual bool isTraversable(const Eigen::Vector3d &position, const Eigen::Quaterniond &orientation) override;

            // check whether point is part of the map
            virtual bool isObserved(const Eigen::Vector3d &point) override;

            // get occupancy
            virtual unsigned char getVoxelState(const Eigen::Vector3d &point) override;

            // get voxel size
            virtual double getVoxelSize() override;

            // get the center of a voxel from input point
            virtual bool getVoxelCenter(Eigen::Vector3d *center, const Eigen::Vector3d &point) override;

            // get the stored distance
            virtual double getVoxelDistance(const Eigen::Vector3d &point) override;

            // get the stored weight
            virtual double getVoxelWeight(const Eigen::Vector3d &point) override;

            // get the maximum allowed weight (return 0 if using uncapped weights)
            virtual double getMaximumWeight() override;

            // accessor to the server for specialized planners
            voxblox::EsdfServer &getESDFServer();

        protected:
            static ModuleFactoryRegistry::Registration<VoxbloxMap> registration;

            // esdf server that contains the map, subscribe to external ESDF/TSDF updates
            std::unique_ptr<voxblox::EsdfServer> esdf_server_;

            // cache constants
            double c_voxel_size_;
            double c_block_size_;
            double c_maximum_weight_;
        };

    } // namespace map
} // namespace active_3d_planning

#endif // ACTIVE_3D_PLANNING_VOXBLOX_MAP_VOXBLOX_H
