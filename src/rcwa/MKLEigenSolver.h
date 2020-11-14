// This file is part of DiffSMat.
// 
// DiffSMat is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// DiffSMat is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with DiffSMat. If not, see <https://www.gnu.org/licenses/>.

#pragma once
#include "defns.h"
#include <Eigen/Core>


class MKLEigenSolver
{
private:
    Eigen::MatrixXcs V_;
    Eigen::VectorXcs d_;

public:
    MKLEigenSolver() {}
    void compute(const Eigen::MatrixXcs& A);
    const Eigen::MatrixXcs& eigenvectors() const { return V_; }
    const Eigen::VectorXcs& eigenvalues() const { return d_; }
};