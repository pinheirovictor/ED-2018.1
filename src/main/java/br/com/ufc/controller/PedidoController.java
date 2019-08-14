package br.com.ufc.controller;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.ModelAndView;

import br.com.ufc.model.Pedido;
import br.com.ufc.model.Prato;
import br.com.ufc.services.PedidoService;
import br.com.ufc.services.PessoaService;

@Controller
@RequestMapping("/outback")
public class PedidoController {

	@Autowired
	private PedidoService pedidoService;

	@Autowired
	private PessoaService clienteService;

	private static List<Prato> listaPedido = new ArrayList<Prato>();

	public static void adicionarPratoAoPedido(Prato prato) {
		listaPedido.add(prato);
	}

	public static void limparCarrinho() {
		listaPedido.clear();
	}

	private float valorTotalCarrinho() {
		float total = 0;
		for (Prato prato : listaPedido) {
			total += prato.getPreco();
		}
		return total;
	}

	@RequestMapping("/vercarrinho")
	public ModelAndView listarPedidos() {
		ModelAndView mv = new ModelAndView("listaPedido");//mudar isso
		mv.addObject("listaPratosPedido", listaPedido);
		mv.addObject("valorTotal", valorTotalCarrinho());
		return mv;
	}

	@RequestMapping("/confirmar")
	public ModelAndView confirmarPedido(@RequestParam(value = "enderecoPedido") String endereco) {
		Pedido pedido = new Pedido();
		pedido.setEnderecoPedido(endereco);
		pedido.setValorTotal(valorTotalCarrinho());

		pedido.setCodigoCliente(clienteService.getPessoaSession().getCodigo());
		String pratoPedido = "";
		for (Prato prato : listaPedido) {
			pratoPedido += prato.getNome() + "," + "R$" + prato.getPreco() + "\n";
		}
		System.out.println(pratoPedido);
		pedido.setPratosPedido(pratoPedido);

		pedidoService.cadastrar(pedido);
		ModelAndView mv = new ModelAndView("paginainicial");

		limparCarrinho();
		return mv;
	}

	@RequestMapping("/excluirpedido/{codigo}")
	public ModelAndView excluirPratoDoPedido(@PathVariable Long codigo) {
		for (Prato prato : listaPedido) {
			if (prato.getCodigo() == codigo) {
				listaPedido.remove(prato);
				break;
			}
		}
		ModelAndView mv = new ModelAndView("redirect:/outback/vercarrinho");
		return mv;
	}

}
