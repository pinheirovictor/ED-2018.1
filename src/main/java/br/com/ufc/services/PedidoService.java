package br.com.ufc.services;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import br.com.ufc.model.Pedido;
import br.com.ufc.repository.PedidoRepository;

@Service
public class PedidoService {

	@Autowired
	private PedidoRepository pedidoRepository;

	public void cadastrar(Pedido pedido) {
		pedidoRepository.save(pedido);
	}

	public List<Pedido> listarPedidosPorId(Long pessoaCodigo) {
		List<Pedido> pessoaPedidos = new ArrayList<Pedido>();
		for (Pedido pedido : pedidoRepository.findAll()) {
			if (pedido.getCodigoCliente() == pessoaCodigo) {
				pessoaPedidos.add(pedido);
			}
		}
		return pessoaPedidos;
	}

	public void excluir(Long codigo) {
		pedidoRepository.deleteById(codigo);
	}

	public Pedido buscar(Long codigo) {
		return pedidoRepository.getOne(codigo);
	}

}
