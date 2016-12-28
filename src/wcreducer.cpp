
using std::string;
using std::cout;

class reducer
{
public:
    void reduce(std::string key, wmr::datastream stm)
    {
        long sum = 0;
        string value;
	// int accumulate = 0;
	// float avg;

	
        // grab data from the stream until there are no more values
        while (!stm.eof())
        {
            stm >> value;
	    // accumulate++;
            // convert the value to a number, then add it to the
            // running total
            sum += wmr::utility::fromString<long>(value);
	    // avg = sum/accumulate;
        }
        // emit the key with its total count
        wmr::emit(key, sum);
    }
};

