#include <string>

#include <TTree.h>
#include <TDataType.h> //for getType
#include <TClass.h>    //for getType

/** 
 * @brief This class is a container class that contains a TBranch.
 *
 * It is used as a struct that contains a reference to the
 * TBranch and the corresponding variable name. It is useful
 * because TBranch has a lot of unnecessary information for analysis
 * and has no method that returns the variable type. Since we deal
 * both with integer histograms and float histograms a method as such
 * is of great convenience.
 *
 */
class Branch {
   friend class Tree;
   private:
      TBranch *tbranch; ///<Points to containing TBranch
      std::string name; ///<Name of branch variable

   public:
      Branch(TTree *tree, std::string name); ///<Constructor
      Int_t getType() const;                 ///<Return the var type of the Branch content
};
