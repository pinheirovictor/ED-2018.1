package br.com.ufc.security;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Repository;

import br.com.ufc.model.Pessoa;
import br.com.ufc.repository.PessoaRepository;

@Repository
public class UserDetailsServiceImplementacao implements UserDetailsService {

	@Autowired
	private PessoaRepository pessoaRepository;

	@Override
	public UserDetails loadUserByUsername(String email) throws UsernameNotFoundException {
		Pessoa pessoa = pessoaRepository.findByEmail(email);

		if (pessoa == null) {
			throw new UsernameNotFoundException("pessoa não encontrada!!!");
		}
		return new User(pessoa.getUsername(), pessoa.getPassword(), true, true, true, true, pessoa.getAuthorities());
	}

}
