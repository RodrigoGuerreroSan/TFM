// Solve the Temperature equation

  fvScalarMatrix TEqn
(
    fvm::ddt(T) 
  + fvm::div(phi, T)
 ==
    fvm::laplacian(alphaTh,T)
);

TEqn.relax();

TEqn.solve();
