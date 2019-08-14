package br.com.ufc.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import br.com.ufc.model.Pessoa;
import br.com.ufc.model.Prato;

@Repository
public interface PessoaRepository extends JpaRepository<Pessoa, Long>{

	Pessoa findByEmail(String email);

	
	
}
