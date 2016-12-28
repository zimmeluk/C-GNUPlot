using std::string;
using std::cout;

class reducer
{
public:
    void reduce(std::string key, wmr::datastream stm)
    {
        float sum = 0;
        string value;
	float accumulate = 0;
	float avg;

	
        // grab data from the stream until there are no more values
        while (!stm.eof())
        {
            stm >> value;
	    // remove unknown values for a more accurate average
	    // unknown values in the data are marked -9
	    if(wmr::utility::fromString<long>(value) != -9){
	      accumulate++;
	      // convert the value to a number, then add it to the
	      // running total
	      sum += wmr::utility::fromString<long>(value);
	  }
        }
        // emit the key with its total count
	avg = sum/accumulate;
	// eliminate the junk data
	if(wmr::utility::fromString<int>(key) > 10)
	  wmr::emit(key, avg);
    }
};
