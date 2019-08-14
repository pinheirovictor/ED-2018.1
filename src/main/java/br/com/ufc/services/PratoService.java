package br.com.ufc.services;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import br.com.ufc.model.Prato;
import br.com.ufc.repository.PratoRepository;
import br.com.ufc.util.PratoFileUtils;

@Service
public class PratoService {

	@Autowired
	private PratoRepository pratoRepository;

	// metodo cadastrar prato
	public void cadastrar(Prato prato, MultipartFile imagem) {
		String caminho = "images/" + prato.getNome() + ".png";
		PratoFileUtils.salvarImagem(caminho, imagem);
		pratoRepository.save(prato);
	}

	public List<Prato> listar() {
		return pratoRepository.findAll();
	}

	public void excluir(Long codigo) {
		pratoRepository.deleteById(codigo);
	}

	public Prato buscarPorId(Long codigo) {
		return pratoRepository.getOne(codigo);
	}

	public Prato obterPrato(Long idPrato) {
		return pratoRepository.getOne(idPrato);
	}

	public List<Prato> retornarPratos() {
		return pratoRepository.findAll();
	}

	public void excluirPrato(Long id) {
		String caminho = "imagens/pratos/" + id + ".jpg";
		System.out.println(caminho);
		PratoFileUtils.apagarImagem(caminho);
		pratoRepository.deleteById(id);
	}

	public Prato buscarPrato(Long id) {
		return pratoRepository.getOne(id);
	}
}
