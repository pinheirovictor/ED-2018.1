package br.com.ufc.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import br.com.ufc.model.Pessoa;
import br.com.ufc.model.Prato;
import br.com.ufc.services.PratoService;

@Controller
@RequestMapping("/outback")
public class PratoController {

	@Autowired
	private PratoService pratoService;

	@RequestMapping("/cadastrarpratos")
	public ModelAndView form() {
		ModelAndView mv = new ModelAndView("cadastropratos");
		mv.addObject("prato", new Prato());
		mv.addObject("texto", "Cadastrar");
		return mv;
	}

	@RequestMapping("/salvarpratos")
	public ModelAndView salvarPessoa(@Validated Prato prato, BindingResult result,
			@RequestParam(value = "imagem") MultipartFile imagem) {
		ModelAndView mv = new ModelAndView("cadastropratos");
		if (result.hasErrors()) {
			return mv;
		}
		pratoService.cadastrar(prato, imagem);
		mv.addObject("mensagem", "Pessoa cadastrada com Sucesso!!!");

		mv.addObject("pessoa", new Prato());
		mv.addObject("texto", "Cadastrar");
		return mv;
	}

	@RequestMapping("/cardapio")
	public ModelAndView cardapio() {
		List<Prato> pratos = pratoService.listar();
		ModelAndView mv = new ModelAndView("cardapio");
		mv.addObject("listaDePratos", pratos);
		return mv;
	}

	@RequestMapping("/listarpratos")
	public ModelAndView listarPratos() {
		// trazer do banco
		List<Prato> pratos = pratoService.listar();

		ModelAndView mv = new ModelAndView("PaginaListagem");
		mv.addObject("listaDePratos", pratos);
		return mv;
	}

	@RequestMapping("/excluir/{codigo}")
	public ModelAndView excluir(@PathVariable Long codigo) {
		pratoService.excluir(codigo);
		ModelAndView mv = new ModelAndView("redirect:/outback/listarpratos");
		return mv;
	}

	/*
	 * @RequestMapping("/listar") public ModelAndView listar() { List<Prato> pratos
	 * = pratoService.listar(); ModelAndView mv = new ModelAndView("listarPratos");
	 * mv.addObject("listaPratos", pratos); return mv; }
	 */

	@RequestMapping("/alterar/{codigo}")
	public ModelAndView alterar(@PathVariable Long codigo) {
		Prato prato = pratoService.buscarPorId(codigo);
		ModelAndView mv = new ModelAndView("cadastropratos");
		mv.addObject("prato", prato);
		mv.addObject("texto", "Atualizar");
		return mv;
	}

	@RequestMapping("/comprar/{codigo}")
	public ModelAndView comprarPrato(@PathVariable Long codigo) {
		Prato prato = pratoService.buscarPorId(codigo);
		PedidoController.adicionarPratoAoPedido(prato);
		System.out.println(prato);
		ModelAndView mv = new ModelAndView("redirect:/outback/vercarrinho");
		return mv;
	}

}
