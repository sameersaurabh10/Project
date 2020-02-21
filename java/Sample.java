import java.util.Scanner;

public class Sample {

	public static String remove_extra_char(String data) {
		String temp = "";

		for(int i = 0; i< data.length(); i++) {
			if(!(data.charAt(i) =='-' || data.charAt(i)=='/')) {
				temp = temp + data.charAt(i) + "";
			}
		}
		return temp;
	}
	
	public static boolean validateDate(String data) {
		for (int i = 0; i < data.length(); i++) {
			if(!Character.isDigit(data.charAt(i)))
				return false;
		}
		return true;
	}

	public static int getDigitSum(int data) {
		int sum = 0;
		while(data > 0) {
			sum = sum + data % 10;
			data = data / 10;
		}
		return sum;
	}
	public static int getLuckyNumber(int data) {
		int res;

			res = getDigitSum(data);
			if(res >=0 && res <10)
				return res;
			return getLuckyNumber(res);
	}



	public static void main(String[] args) {
		int res;
		Scanner sc = new Scanner(System.in);

		System.out.print("Enter DOB : ");
		String data1 = sc.nextLine();
		System.out.println("Given DOB : " + data1);
		String data = remove_extra_char(data1);

		if (data != null) {
			if(!validateDate(data))
				System.out.println("Provide DOB in proper format");
			else {
				res = getLuckyNumber(Integer.parseInt(data));
				System.out.println("Lucky Number : " + res);
			}
		} else {
			System.out.println("Provide DOB in proper format");
		}
			
	}
}
