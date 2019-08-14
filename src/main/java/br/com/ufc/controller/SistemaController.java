package br.com.ufc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
@RequestMapping("/outback")
public class SistemaController {

	/*
	 * @RequestMapping("/home") public String index() { return "index"; }
	 */

	@RequestMapping("/paginainicial")
	public String paginaInicial() {
		return "paginaInicial";
	}

	@RequestMapping("/login")
	public ModelAndView login() {
		ModelAndView mv = new ModelAndView("/login");
		return mv;
	}

	@RequestMapping("/destaques")
	public String destaques() {
		return "destaques";
	}

	@RequestMapping("/quemsomos")
	public String quemSomos() {
		return "quemsomos";
	}

	@RequestMapping("/faleconosco")
	public String faleConosco() {
		return "faleconosco";
	}

}
