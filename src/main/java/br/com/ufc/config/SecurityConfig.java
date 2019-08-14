package br.com.ufc.config;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.builders.WebSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

import br.com.ufc.security.UserDetailsServiceImplementacao;

@Configuration
@EnableWebSecurity
public class SecurityConfig extends WebSecurityConfigurerAdapter {

	@Autowired
	private UserDetailsServiceImplementacao userDetailsServiceImple;

	@Override
	protected void configure(HttpSecurity http) throws Exception {
		http.csrf().disable().authorizeRequests()

				.antMatchers("/outback/paginainicial").permitAll()
				.antMatchers("/outback/destaques").permitAll()
				.antMatchers("/outback/quemsomos").permitAll()
				.antMatchers("/outback/faleconosco").permitAll()
				.antMatchers("/outback/cardapio").permitAll()
				.antMatchers("/outback/cadastrarcliente").permitAll()
				.antMatchers("/outback/salvarcliente").permitAll()

				/*
				 * .antMatchers("/outback/atual").hasRole("USER")
				 * .antMatchers("/outback/finalizar").hasRole("USER")
				 * .antMatchers("/outback/finalizados").hasRole("USER")
				 */

				 .antMatchers("/outback/adicionarPrato/{id}").hasRole("USER")
				 .antMatchers("/outback/listarpedidos").hasRole("USER")
				 .antMatchers("/outback/fecharpedido").hasRole("USER")
				 .antMatchers("/outback/removerPrato/{id}").hasRole("USER")
				
				.antMatchers("/outback/cadastrarpratos").hasRole("ADMIN")
				.antMatchers("/outback/salvarpratos").hasRole("ADMIN")
				.antMatchers("/outback/listarpratos").hasRole("ADMIN")
				.antMatchers("/outback/listarcliente").hasRole("ADMIN")

				.anyRequest().authenticated()

				.and()
				.formLogin()
				.loginPage("/outback/login").permitAll().defaultSuccessUrl("/outback/paginainicial")

				.and()
				.logout()
				.logoutSuccessUrl("/logout")
				.logoutSuccessUrl("/outback/paginainicial").permitAll();
	}

	@Override
	protected void configure(AuthenticationManagerBuilder auth) throws Exception {
		auth.userDetailsService(userDetailsServiceImple).passwordEncoder(new BCryptPasswordEncoder());
	}

	@Override
	public void configure(WebSecurity web) throws Exception {
		web.ignoring().antMatchers("/css/**", "/js/**", "/img/**", "/images/**");
	}

}
