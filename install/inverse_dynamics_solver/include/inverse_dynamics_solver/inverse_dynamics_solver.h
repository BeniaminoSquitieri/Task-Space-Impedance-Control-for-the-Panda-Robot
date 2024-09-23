/* -------------------------------------------------------------------
 *
 * This module has been developed by the Automatic Control Group
 * of the University of Salerno, Italy.
 *
 * Title:   inverse_dynamics_solver.h
 * Author:  Enrico Ferrentino, Vincenzo Petrone
 * Org.:    UNISA
 * Date:    Dec 3, 2019
 *
 * This class is a plugin interface for dynamic solvers, that are
 * solvers providing the dynamic parameters of a given robot, namely
 * inertia matrix, Coriolis vector, gravity vector and friction
 * vector.
 *
 * -------------------------------------------------------------------
 */

#pragma once

#include <vector>
#include <memory>
#include <eigen3/Eigen/Core>

namespace inverse_dynamics_solver {

class InverseDynamicsSolver {
  public:
    /**
     * @brief Virtual destructor
     */
    virtual ~InverseDynamicsSolver() {}

    /**
     * @brief Initializes the plugin object
     *
     * Since pluginlib requires the implementation to have a parameterless
     * constructor, the objects are initialized through this method
     *
     * @param link_names names of links composing the kinematic chain
     */
    virtual void initialize(const std::vector<std::string>& link_names) = 0;

    /**
     * @brief Get all the dynamic parameters at once
     *
     * @param joint_positions joint positions
     * @param joint_velocities joint velocities
     * @return inertia matrix, Coriolis vector, corresponding to C(q,qd)*qd and gravity vector
     */
    virtual std::tuple<Eigen::MatrixXd, Eigen::VectorXd, Eigen::VectorXd> getDynamicParameters(const Eigen::VectorXd& joint_positions,
                                                                                               const Eigen::VectorXd& joint_velocities) const = 0;

    /**
     * @brief Get the inertia matrix
     *
     * @param joint_positions joint positions
     * @return inertia matrix
     */
    virtual Eigen::MatrixXd getInertiaMatrix(const Eigen::VectorXd& joint_positions) const = 0;

    /**
     * @brief Get the Coriolis vector
     *
     * @param joint_positions joint positions
     * @param joint_velocities joint velocities
     * @return coriolis vector, corresponding to C(q,qd)*qd
     */
    virtual Eigen::VectorXd getCoriolisVector(const Eigen::VectorXd& joint_positions, const Eigen::VectorXd& joint_velocities) const = 0;

    /**
     * @brief Get the gravity vector
     *
     * @param joint_positions input joint positions
     * @return gravity vector
     */
    virtual Eigen::VectorXd getGravityVector(const Eigen::VectorXd& joint_positions) const = 0;

    /**
     * @brief Get the vector of friction torques
     *
     * @param joint_velocities input joint velocities
     * @return viscous friction vector
     */
    virtual Eigen::VectorXd getFrictionVector(const Eigen::VectorXd& joint_velocities) const = 0;

    /**
     * @brief Get the vector of torques due to Coriolis effects, inertia and gravity
     *
     * @param joint_positions input joint positions
     * @param joint_velocities input joint velocities
     * @param joint_accelerations input joint accelerations
     * @return torques vector
     */
    virtual Eigen::VectorXd getTorques(const Eigen::VectorXd& joint_positions, const Eigen::VectorXd& joint_velocities,
                                       const Eigen::VectorXd& joint_accelerations) const {
        return getInertiaMatrix(joint_positions) * joint_accelerations + getCoriolisVector(joint_positions, joint_velocities) +
               getGravityVector(joint_positions);
    }

  protected:
    InverseDynamicsSolver() {}
};

}  // namespace inverse_dynamics_solver
