import javax.xml.crypto.dsig.spec.XSLTTransformParameterSpec;

public class TestMain {
    public static void main(String[] args) {
        Manager boss = new Manager("Linus", 45, 180, 8000);

        var staff = new Employee[3];

        staff[0] = boss;
        staff[1] = new Employee("A", 20, 170, 5000);
        staff[2] = new Employee("B", 21, 170, 5000);
        staff[0].equals(staff[1]);
        for (Employee e: staff)
            System.out.println(e.getName() + " " + e.getOld() + " " + e.getSalary());
        for (Employee e: staff)
            System.out.println(e.hashCode());

        for (Employee e: staff)
            System.out.println(e.toString());



    }
}
