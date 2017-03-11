
#include <G4Tubs.hh>
#include <G4AssemblyVolume.hh>
#include "DetGeometry.hh"
#include <G4PhysicalConstants.hh>
DetGeometry::DetGeometry() {
    world_sizeXYZ   = 50 * m;
    nist            = G4NistManager::Instance();
    world_mat       = nist->FindOrBuildMaterial("G4_AIR");
    solidWorld      = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
    logicWorld      = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
    physWorld       = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);
    G4cout<<"Geometry of detector is build successfully\t\t\t\t\t\tOK!!!"<<G4endl;
}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){


    G4Tubs *tub1 =new G4Tubs("tubs1",0,100*mm,25*mm,0,360*deg);
    G4LogicalVolume *log_tub1 = new G4LogicalVolume(tub1,world_mat,"log_tubs");
 //   new G4PVPlacement (0,G4ThreeVector(),log_tub1,"phy_tub1",LogicWorld, false,0);

    G4Tubs *tub2 =new G4Tubs("tubs2",75,100*mm,250*mm,0,360*deg);
    G4LogicalVolume *log_tub2 = new G4LogicalVolume(tub2,world_mat,"log_tub2");
 //   new G4PVPlacement (0,G4ThreeVector(),log_tub2,"phy_tub1",logicWorld, false,0);

G4AssemblyVolume* tubs= new G4AssemblyVolume();
    G4ThreeVector vect(0,0,(25+100)*mm);
     tubs->AddPlacedVolume(log_tub1,vect,0);
     G4ThreeVector nullvect(0,0,0);
     tubs->AddPlacedVolume(log_tub2,nullvect,0);

    tubs->MakeImprint(logicWorld,nullvect,0,0,false);


    G4ThreeVector av_vect(0,0,-800*mm);
    tubs->MakeImprint(logicWorld,av_vect,new G4RotationMatrix(0,pi,0),0,false);



    return physWorld;
}


