    IOobject UMeanHeader
    (
        "UMean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ
    );

    if (!UMeanHeader.typeHeaderOk<volVectorField>(true))
    {
        Info<< "    No UMean field" << endl;
        continue;
    }

    volVectorField UMean
    (
        UMeanHeader,
        mesh
    );

    volSymmTensorField UPrime2Mean
    (
        IOobject
        (
            "UPrime2Mean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );
    volScalarField Rxx(UPrime2Mean.component(symmTensor::XX));
    volScalarField Ryy(UPrime2Mean.component(symmTensor::YY));
    volScalarField Rzz(UPrime2Mean.component(symmTensor::ZZ));
    volScalarField Rxy(UPrime2Mean.component(symmTensor::XY));

    volScalarField pPrime2Mean
    (
        IOobject
        (
            "pPrime2Mean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    /*
    volScalarField epsilonMean
    (
        IOobject
        (
            "epsilonMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volScalarField nuMean
    (
        IOobject
        (
            "nuMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volScalarField gammaDotMean
    (
        IOobject
        (
            "gammaDotMean",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );

    volScalarField nuPrime2
    (
        IOobject
        (
            "nuPrime",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );
    volScalarField nuPrime = sqrt(mag(nuPrime2 - sqr(nuMean)));


    volScalarField gammaDotPrime2
    (
        IOobject
        (
            "gammaDotPrime",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ
        ),
        mesh
    );
    volScalarField gammaDotPrime = sqrt(mag(gammaDotPrime2 -sqr(gammaDotMean)));
    */
volSymmTensorField BMean
(
IOobject
(
"BMean",
runTime.timeName(),
mesh,
IOobject::MUST_READ
),
mesh
);
volScalarField Bxx(BMean.component(symmTensor::XX));
volScalarField Byy(BMean.component(symmTensor::YY));
volScalarField Bzz(BMean.component(symmTensor::ZZ));
volScalarField Bxy(BMean.component(symmTensor::XY));
volSymmTensorField nuGradUMean
(
IOobject
(
"nuGradUMean",
runTime.timeName(),
mesh,
IOobject::MUST_READ
),
mesh
);
volScalarField nuGradUxx(nuGradUMean.component(symmTensor::XX));
volScalarField nuGradUyy(nuGradUMean.component(symmTensor::YY));
volScalarField nuGradUzz(nuGradUMean.component(symmTensor::ZZ));
volScalarField nuGradUxy(nuGradUMean.component(symmTensor::XY));