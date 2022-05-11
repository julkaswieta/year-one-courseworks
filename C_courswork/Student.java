/** 
 * @author Brian Kernighan
 */
public class Student {

    private int matric;
    private String name;
    private String address;

    /**
     * Query for the matric number of the student.
     * @return the matric
     */
    public int getMatric (  ) {
        return this.matric;
    }

    /**
     * Sets the matric number of the student.
     * @param matric the matric number
     */
    public void setMatric ( int matric ) {
        this.matric = matric;
    }

    /**
     * Query for the name of the student.
     * @return the name
     */
    public String getName ( ) {
        return this.name;
    }

    /**
     * Sets the name of the student.
     * @param name the name
     */
    public void setName ( String name ) {
        this.name = name;
    }

    /**
     * Query for the address of the student.
     * @return the address
     */
    public String getAddress ( ) {
        return this.address;
    }

    /**
     * Sets the address of the student.
     * @param address the address
     */
    public void setAddress ( String address ) {
        this.address = address;
    }

    /**
     * @return a string representation of the Student
     */
    public String toString ( ) {
        return this.matric + "," + this.name + "," + this.address;
    }

}