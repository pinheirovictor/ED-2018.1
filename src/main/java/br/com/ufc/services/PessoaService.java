package br.com.ufc.services;

import java.util.ArrayList;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import br.com.ufc.model.Pessoa;
import br.com.ufc.model.Role;
import br.com.ufc.repository.PessoaRepository;

@Service
public class PessoaService {

	@Autowired
	private PessoaRepository pessoaRepository;

	public Pessoa getPessoaSession() {
		Object auth = SecurityContextHolder.getContext().getAuthentication().getPrincipal();
		UserDetails user = (UserDetails) auth;
				
		Pessoa cliente = buscarPorEmail(user.getUsername());
		return cliente;
	}

	
	public void cadastrarPessoa(Pessoa pessoa) {
		pessoa.setSenha(new BCryptPasswordEncoder().encode(pessoa.getSenha()));
		Role papel = new Role();
		papel.setpapel("ROLE_USER");
		List<Role> roles = new ArrayList<Role>();
		roles.add(papel);
		pessoa.setRoles(roles);
		pessoaRepository.save(pessoa);
	}

	public List<Pessoa> listar() {
		return pessoaRepository.findAll();
	}

	public Pessoa buscarPorId(Long codigo) {
		return pessoaRepository.getOne(codigo);
	}

	public Pessoa buscarPorEmail(String email) {
		return pessoaRepository.findByEmail(email);
	}

}
