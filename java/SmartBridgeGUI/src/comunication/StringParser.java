package comunication;

import java.util.Map;

public interface StringParser {

	/**
	 * Splits the message given and stores in the used data structure
	 */
	public Map<DataRead, String> parse(String msg);
	
}
