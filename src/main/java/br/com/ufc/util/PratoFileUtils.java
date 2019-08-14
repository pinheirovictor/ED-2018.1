package br.com.ufc.util;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;
import org.springframework.web.multipart.MultipartFile;

public class PratoFileUtils {

	// metodo salvar
	public static void salvarImagem(String caminho, MultipartFile imagem) {
		File file = new File(caminho);
		try {
			FileUtils.writeByteArrayToFile(file, imagem.getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// meotodo deletar iamgem
	public static void apagarImagem(String caminho) {
		System.out.println("caminho da imagem: " + caminho);
		File file = new File(caminho);
		file.delete();
	}

}
