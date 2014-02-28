#include "Branch.h"



///Constructor
Branch::Branch(TTree *tree, std::string varname)
{
   name = varname;
   TBranch *branch = tree->GetBranch(varname.c_str());
   tbranch = branch;
}
/**< 
 * The constructor sets the two parameters to the corresponding member variables.
 * The TBranch has to be extracted from the TTree first.
 *
 * @param *tree Points to the TTree that is this Branch's parent
 * @param varname Name of the TBranch to be referred in this Branch container
 *
 */



///Return the var type of the Branch content
Int_t Branch::getType() const
{
   TClass *tclass = new TClass();
   EDataType type;
   tbranch->GetExpectedType(*&tclass, type);

   return type;
}
/**<
 * This method uses TDataType to determine the EDataType enumeration 
 * that correponds to the variables saved in this TBranch.
 *
 * @return int corresponding to the following enum table.
 *
 * The relevant output (so far) is 5 for Float_t and 13 for UInt_t
 *
 * From http://root.cern.ch/root/html532/TDataType.h :
 *
 * enum EDataType {
 *    kChar_t   = 1,  kUChar_t  = 11, kShort_t    = 2,  kUShort_t = 12,
 *    kInt_t    = 3,  kUInt_t   = 13, kLong_t     = 4,  kULong_t  = 14,
 *    kFloat_t  = 5,  kDouble_t =  8, kDouble32_t = 9,  kchar     = 10,
 *    kBool_t   = 18, kLong64_t = 16, kULong64_t  = 17, kOther_t  = -1,
 *    kNoType_t = 0,  kFloat16_t= 19,
 *    kCounter  =  6, kCharStar = 7,  kBits     = 15,
 *    kVoid_t   = 20,
 * 
 *    kDataTypeAliasUnsigned_t = 21,
 *    kNumDataTypes
 * }
 */
