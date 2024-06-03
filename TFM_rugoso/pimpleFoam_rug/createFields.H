#include "createRDeltaT.H"

Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"


label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, pimple.dict(), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());


singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

#include "createMRF.H"
#include "createFvOptions.H"




volSymmTensorField nuGradU  //Turbulent viscosity
(
IOobject
(
"nuGradU",
runTime.timeName(),
mesh,
IOobject::NO_READ,
IOobject::AUTO_WRITE
),
laminarTransport.nu()*-2*dev(symm(fvc::grad(U)))
);


volSymmTensorField B  //Wall shear stress
(
IOobject
(
"B",
runTime.timeName(),
mesh,
IOobject::NO_READ,
IOobject::AUTO_WRITE
),
laminarTransport.nu()*-2*dev(symm(fvc::grad(U)))
);