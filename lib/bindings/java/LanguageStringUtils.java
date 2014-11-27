package Language;

/**
 * 
 * @author danielortiz
 *
 */
public class LanguageStringUtils{
	static{
		System.loadLibrary("Language");			// Load the language string utils
	}
	
	/**
	 * Get the length of a java string
	 * @param str A java string to get the length
	 * @param enconding The encoding of the java string
	 */
	public native length(String str, int encoding);
};