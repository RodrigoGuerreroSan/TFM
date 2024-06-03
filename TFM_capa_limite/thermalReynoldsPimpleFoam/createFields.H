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

volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

IOdictionary thermalProperties
(
    IOobject
    (
        "thermalProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

dimensionedScalar alphaTh  //add
(
    thermalProperties.lookup("alphaTh")
);

dimensionedScalar Cp  //add
(
    thermalProperties.lookup("Cp")
);

IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

dimensionedScalar rho  //add
(
    transportProperties.lookup("rho")
);

dimensionedScalar L  //add
(
    transportProperties.lookup("L")
);

dimensionedScalar V  //add
(
    transportProperties.lookup("V")
);

dimensionedScalar Re  //add
(
    transportProperties.lookup("Re")
);

dimensionedScalar mu  //add
(
    transportProperties.lookup("mu")
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

Info<< "Reading diffusivity DT\n" << endl;

dimensionedScalar DT("DT", dimViscosity, transportProperties);

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

