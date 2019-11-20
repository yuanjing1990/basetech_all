package Thread;

import java.io.*;

class CopyTest {
	public static void main(String args[]) {
		if (args.length < 2) {
			System.out.println("Usage:java CopyTest file1 file2");
			System.exit(-1);
		}
		FileInputStream ifs = null;
		FileOutputStream ofs = null;
		try {
			ofs = new FileOutputStream(args[0]);
			ifs = new FileInputStream(args[1]);
			copyFile(ifs, ofs);
		} catch (FileNotFoundException e) {
			System.out.println("File" + args[0] + "not found or permission denied!");
			System.exit(-2);
		}
	}

	private static void copyFile(FileInputStream file1, FileOutputStream file2) {
		int nLength;
		byte buffer[] = new byte[512];
		try {
			while ((nLength = file1.read(buffer, 0, 512)) != -1) {
				file2.write(buffer, 0, nLength);
			}
		} catch (IOException e) {
			System.out.println(e);
			System.exit(-4);
		}
	}
}