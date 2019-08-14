package br.com.ufc.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import br.com.ufc.model.Pedido;
import br.com.ufc.model.Pessoa;
import br.com.ufc.model.Prato;
import br.com.ufc.services.PedidoService;
import br.com.ufc.services.PessoaService;
import br.com.ufc.services.PratoService;

@Controller
@RequestMapping("/outback")
public class PessoaController {

	@Autowired
	private PessoaService pessoaService;

	@Autowired
	private PedidoService pedidoService;
	
	@Autowired
	private PratoService pratoService;
	
	private PedidoController ps;

	@RequestMapping("/cadastrarcliente")
	public ModelAndView cadastrar() {
		ModelAndView mv = new ModelAndView("cadastroCliente");
		mv.addObject("pessoa", new Pessoa());
		mv.addObject("texto", "Cadastrar");
		return mv;
	}

	@RequestMapping("/salvarcliente")
	public ModelAndView salvarPessoa(@Validated Pessoa pessoa, BindingResult result) {
		ModelAndView mv = new ModelAndView("cadastroCliente");
		if (result.hasErrors()) {
			return mv;
		}
		pessoaService.cadastrarPessoa(pessoa);
		mv.addObject("mensagem", "Pessoa cadastrada com Sucesso!!!");

		mv.addObject("pessoa", new Pessoa());
		return mv;
	}

	@RequestMapping("/listarcliente")
	public ModelAndView listarPessoas() {
		// trazer do banco
		List<Pessoa> pessoas = pessoaService.listar();

		ModelAndView mv = new ModelAndView("listagemclientes");
		mv.addObject("listaDePessoas", pessoas);
		return mv;
	}

	@RequestMapping("/listarpedidos")
	public ModelAndView listarPedidos() {
		ModelAndView mv = new ModelAndView("historicoPedidos");// mudar isso
		Object auth = SecurityContextHolder.getContext().getAuthentication().getPrincipal();

		UserDetails user = (UserDetails) auth;

		Pessoa cliente = pessoaService.buscarPorEmail(user.getUsername());
		List<Pedido> pedidos = pedidoService.listarPedidosPorId(cliente.getCodigo());

		mv.addObject("historicoPedidos", pedidos);
		return mv;
	}


}
