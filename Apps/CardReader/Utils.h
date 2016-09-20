//---------------------------------------------------------------------------

#ifndef UtilsH
#define UtilsH
//---------------------------------------------------------------------------

#include "DBIntf.h"
#include "Database.h"
#include "PGLibraryLoader.h"
#include "AnsiString.h"
#include "Exception.h"
#include "Utf8Util.h"

#include <map>

#include "data/AppData.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <fstream>


DynSet<DoctorSet> getPbxDoctors(DBIntf& );
DynSet<NilDoctor> getNilDoctors(DBIntf& );
void updateDoctorStatus(DynSet<DoctorSet>&, DynSet<NilDoctor>&, DynSet<DoctorIdent>&, DBIntf& db);
DynSet<DoctorIdent> getNoNilList(DBIntf&);

#endif
