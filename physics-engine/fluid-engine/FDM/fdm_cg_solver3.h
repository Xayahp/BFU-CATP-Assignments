#ifndef HINAPE_FDM_CG_SOLVER3_H
#define HINAPE_FDM_CG_SOLVER3_H
#include "fdm_linear_system_solver3.h"

namespace HinaPE {

//! \brief 3-D finite difference-type linear system solver using conjugate
//!        gradient.
    class FdmCgSolver3 final : public FdmLinearSystemSolver3 {
    public:
        //! Constructs the solver with given parameters.
        FdmCgSolver3(unsigned int maxNumberOfIterations, double tolerance);

        //! Solves the given linear system.
        bool solve(FdmLinearSystem3* system) override;

        //! Solves the given compressed linear system.
        bool solveCompressed(FdmCompressedLinearSystem3* system) override;

        //! Returns the max number of CG iterations.
        unsigned int maxNumberOfIterations() const;

        //! Returns the last number of CG iterations the solver made.
        unsigned int lastNumberOfIterations() const;

        //! Returns the max residual tolerance for the CG method.
        double tolerance() const;

        //! Returns the last residual after the CG iterations.
        double lastResidual() const;

    private:
        unsigned int _maxNumberOfIterations;
        unsigned int _lastNumberOfIterations;
        double _tolerance;
        double _lastResidual;

        // Uncompressed vectors
        FdmVector3 _r;
        FdmVector3 _d;
        FdmVector3 _q;
        FdmVector3 _s;

        // Compressed vectors
        VectorND _rComp;
        VectorND _dComp;
        VectorND _qComp;
        VectorND _sComp;

        void clearUncompressedVectors();
        void clearCompressedVectors();
    };

//! Shared pointer type for the FdmCgSolver3.
    typedef std::shared_ptr<FdmCgSolver3> FdmCgSolver3Ptr;

}
#endif //HINAPE_FDM_CG_SOLVER3_H
