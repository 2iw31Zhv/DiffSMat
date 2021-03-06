# DiffSMat

`DiffSMat` provides the code for the paper

Ziwei Zhu, and Changxi Zheng. [Differentiable Scattering Matrix for Optimization of Photonic Structures](https://arxiv.org/abs/2009.10933). *arXiv preprint* arXiv:2009.10933 (2020).
## Compile
The C++ program is currently built on Ubuntu 18.04. The lastest C++ version (C++17) is recommended.

We use CMake (3.10 or newer) and Make to build the program.

It depends on the following libraries:

- [Eigen 3](http://eigen.tuxfamily.org/index.php?title=Main_Page) (3.1.2 or newer)
- [Intel TBB](https://software.intel.com/content/www/us/en/develop/tools/threading-building-blocks.html) (2.2)
- [Intel Math Kernel Library](https://software.intel.com/content/www/us/en/develop/tools/math-kernel-library.html)

*CBLAS* may be used for acceleration on Mac OS, although this compilation has not been tested on Mac OS.

Please make sure you have the above libraries correctly installed to proceed. Once all dependencies are solved, you can do the following steps to build the program.

Firstly, go to the main directory of this respository (where CMakeLists.txt is).

`cmake .`

You should see *Makefile* is generated in the main folder. Then,

`make`

Once Make is done, you should see a new folder *tests/* is created. These are all the testing programs for our code. 

## Usage

The code provides the derivatives for a single z-invariant device such as meta-atom. You could refer to all the files in *src/tests/* for usage.

For example, in *test5()* of *test_smat_deriv.cpp* you will find the following code. 

` const int N = 23;`

This line specifies half of the harmonics per dimension in xy-plane. Therefore, here we assume 47x47 harmonics. Specifying half of the harmonics is to ensure the number of harmonics for one dimension is always an odd number, which ensures the existence of central harmonic.

    const scalar lambda = 1.55;
    const scalar wx = 1.0;
    const scalar wy = 0.22;
    const scalar wz = 0.31;
The above lines specifies the wavelength and the dimensions of the meta-atom along three axes.


    Eigen::MatrixXcs P, Q, dP, dQ;
    WaveEquationCoeff coeff(N, N, 5., 5.);
    coeff.solve(lambda, wx, wy, P, Q, &dP, nullptr, &dQ, nullptr);
The aboves lines solve for the **P** and **Q** matrices (assuming the period for xy-plane is 5 microns x 5 microns) and the derivative **dP** of **P** with respect to **wx**, and the derivative **dQ** of **Q** with respect to **wx**.


    dtmm::RCWAScatterMatrix rcwa(N, N, 5., 5.);
    rcwa.compute(lambda, wz, P, Q);
The above lines calculate the scattering matrix using **P** and **Q**.

Now you can call
`rcwa.Tuu()`
to get the scattering matrix.

    dtmm::ScatterMatrixDerivative<dtmm::RCWAScatterMatrix> deriv;
    deriv.compute(rcwa, P, Q, dP, dQ);

The above lines use the precomputed **rcwa**, **P**, **Q**, **dP**, and **dQ** to calculate the derivatives of the scattering matrices with respect to **wx**.

Now you can call
`deriv.dTuu()`
to get the derivative of scattering matrix.

We also provide codes for more general grid-based and star-convex-shape-based configuration. Please refer to the code for more details.
