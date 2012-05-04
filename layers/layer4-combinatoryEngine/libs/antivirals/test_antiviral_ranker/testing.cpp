#include <antivirals/antivirals.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	AntiviralSet all_antivirals;
   	DataBase DB(argv[2]);
   	DB.get_antivirals(all_antivirals);

    PseudoNucSequence sequence;
    load_sequence(argv[1], sequence);

    set_default_matrix(matrix);

	AntiviralSet availables_avs;        
	AntiviralSelector av_Selector;

	Rank_Av_Prob result (17);
   	av_Selector.rank_antivirals (all_antivirals,sequence,result);

	//cout <<  "-- sequence size: " << sequence.length() << endl;
	//cout << "-- all_avs count: " << all_antivirals.antivirals.size() << endl << endl;
	cout << " =============== Result================" << endl ;
	for (Rank_Av_Prob::const_iterator it = result.begin(); it!=result.end(); ++it)
	{
        std::string name;
        it->_av.get_attrib("name", name);
		std::cout << "  " << name << "  =  " << it->_prob << std::endl;  
	}

}
 

